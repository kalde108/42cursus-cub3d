#include <pthread.h>

#include "cub3d.h"
#include "libft.h"
#include "tile_address.h"

# include <stdio.h>

static inline void	precompute_steps(t_player *player, t_v2d_d *floor_step, t_v2d_d *floor, size_t y)
{
	t_v2d_d	ray_dir0;
	t_v2d_d	ray_dir1;
	float	row_distance;

	ray_dir0.x = player->dir.x - player->plane.x;
	ray_dir0.y = player->dir.y - player->plane.y;
	ray_dir1.x = player->dir.x + player->plane.x;
	ray_dir1.y = player->dir.y + player->plane.y;
	row_distance = (0.5 * HEIGHT) / (y - (HEIGHT >> 1));
	floor_step->x = row_distance * (ray_dir1.x - ray_dir0.x) / WIDTH;
	floor_step->y = row_distance * (ray_dir1.y - ray_dir0.y) / WIDTH;
	floor->x = player->pos.x + row_distance * ray_dir0.x;
	floor->y = player->pos.y + row_distance * ray_dir0.y;
}

static inline int	get_background_color(t_texdata *texture, t_v2d_d floor, t_v2d_i cell_pos)
{
	t_v2d_i	tex_coord;

	tex_coord.x = (int)(texture->width * (floor.x - cell_pos.x));
	tex_coord.y = (int)(texture->height * (floor.y - cell_pos.y));

	return (((uint32_t *)texture->addr)[texture->width * tex_coord.y + tex_coord.x]);
}

static inline void	background_pixel(t_c3_env *env, t_v2d_d floor, t_v2d_i pixel, t_elem **textures)
{
	t_v2d_i	cell_pos;
	short	cell;

	cell_pos.x = (int)(floor.x);
	cell_pos.y = (int)(floor.y);
	if (cell_pos.x < 0 || cell_pos.x >= env->scene.width || cell_pos.y < 0 || cell_pos.y >= env->scene.height || NOT_FL_CE(env->scene.map[cell_pos.y * env->scene.width + cell_pos.x]))
		return ;
	cell = env->scene.map[cell_pos.y * env->scene.width + cell_pos.x];
	((__uint32_t *)env->img.addr)[pixel.y * WIDTH + pixel.x] = get_background_color(textures[FLOOR][GET_FLOOR(cell)].current, floor, cell_pos);
	((__uint32_t *)env->img.addr)[(HEIGHT - pixel.y - 1) * WIDTH + pixel.x] = get_background_color(textures[CEILING][GET_CEILING(cell)].current, floor, cell_pos);
}

static inline void	background_row(t_c3_env *env, int y, t_elem **textures)
{
	t_v2d_d floor_step;
	t_v2d_d	floor;
	
	precompute_steps(&env->player, &floor_step, &floor, y);
	
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		// if ((int)floor.x >= 0 && (int)floor.x < env->scene.width && (int)floor.y >= 0 && (int)floor.y < env->scene.height && env->scene.map[(int)floor.y * env->scene.width + (int)floor.x] == '0')
		background_pixel(env, floor, (t_v2d_i){x, y}, textures);
		floor.x += floor_step.x;
		floor.y += floor_step.y;
		x++;
	}
}

static void	draw_backgound_chunk(t_c3_env *env, int start, int end)
{
	int		y;

	y = start;
	while (y < end)
	{
		background_row(env, y, env->scene.elems);
		y++;
	}
}

void	*draw_backgound_thread(void *arg)
{
	static int	call = 0;
	t_c3_env	*env;
	int			start;
	int			end;

	env = (t_c3_env *)arg;
	pthread_mutex_lock(&env->call_mutex);
	call++;
	call = call % CPUCORES;
	start = call * ((HEIGHT >> 1) / CPUCORES) + (HEIGHT >> 1);
	end = (call + 1) * ((HEIGHT >> 1) / CPUCORES) + (HEIGHT >> 1);
	// dprintf(2, "start: %d, end: %d\n", start, end);
	pthread_mutex_unlock(&env->call_mutex);
	draw_backgound_chunk(env, start, end);
	return (NULL);
}

int	render_backgound(t_c3_env *env)
{
	pthread_t	threads[CPUCORES];
	int			i;
	int			err;

	err = 0;
	i = 0;
	while (i < CPUCORES)
	{
		err = pthread_create(&threads[i], NULL, draw_backgound_thread, env);
		if (err)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	return (err);
}
