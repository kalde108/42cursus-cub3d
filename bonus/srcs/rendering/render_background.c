#include <pthread.h>

#include "cub3d.h"
#include "libft.h"
#include "tile_address.h"
#include "raycasting.h"

static inline void	precompute_steps(t_camera *camera,
										t_v2d_d *floor_step,
										t_v2d_d *floor,
										size_t y)
{
	t_v2d_d	ray_dir0;
	t_v2d_d	ray_dir1;
	float	row_distance;

	ray_dir0.x = camera->dir.x - camera->plane.x;
	ray_dir0.y = camera->dir.y - camera->plane.y;
	ray_dir1.x = camera->dir.x + camera->plane.x;
	ray_dir1.y = camera->dir.y + camera->plane.y;
	row_distance = (0.5 * HEIGHT) / (y - (HEIGHT >> 1));
	floor_step->x = row_distance * (ray_dir1.x - ray_dir0.x) / WIDTH;
	floor_step->y = row_distance * (ray_dir1.y - ray_dir0.y) / WIDTH;
	floor->x = camera->pos.x + row_distance * ray_dir0.x;
	floor->y = camera->pos.y + row_distance * ray_dir0.y;
}

static inline int	get_background_color(t_texdata *texture,
											t_v2d_d floor,
											t_v2d_i cell_pos)
{
	t_v2d_i	tex_coord;

	tex_coord.x = (int)(texture->width * (floor.x - cell_pos.x));
	tex_coord.y = (int)(texture->height * (floor.y - cell_pos.y));
	return (texture->addr[tex_coord.y * texture->width + tex_coord.x].argb);
}

static inline void	background_pixel(t_c3_env *env,
										t_v2d_d floor,
										t_v2d_i pixel,
										t_elem **textures)
{
	t_v2d_i	cell_pos;
	int		cell;
	int		pos;	// check performance

	cell_pos.x = (int)(floor.x);
	cell_pos.y = (int)(floor.y);
	pos = cell_pos.y * env->scene.width + cell_pos.x;
	if (cell_pos.x < 0
		|| cell_pos.x >= env->scene.width
		|| cell_pos.y < 0
		|| cell_pos.y >= env->scene.height
		|| !IS_FL_CE(env->scene.map[pos]))
		return ;
	cell = env->scene.map[pos];
	(env->img.addr)[pixel.y * WIDTH + pixel.x].argb = \
	get_background_color(textures[FLOOR][GET_FLOOR(cell)].current,
			floor,
			cell_pos);
	(env->img.addr)[(HEIGHT - pixel.y - 1) * WIDTH + pixel.x].argb = \
	get_background_color(textures[CEILING][GET_CEILING(cell)].current,
			floor,
			cell_pos);
}

static inline int	get_camera(t_hit_buffer *buffer, t_camera *camera, int y)
{
	t_hit_buffer	*ptr_buf;
	int				hit_count;
	int				i;

	hit_count = buffer->count;
	i = 0;
	while (i < hit_count)
	{
		ptr_buf = buffer + i;
		if (y <= ptr_buf->y1 || y >= ptr_buf->y2)
		{
			*camera = ptr_buf->camera;
			return (1);
		}
		i++;
	}
	*camera = ptr_buf->camera;
	return (0);
}

static inline void	background_row(t_c3_env *env, int y, t_elem **textures)
{
	t_v2d_d		floor_step;
	t_v2d_d		floor;
	t_camera	old_cam;
	t_camera	camera;
	int			x;

	x = 0;
	old_cam = (t_camera){.pos = (t_v2d_d){-1, -1}};
	while (x < WIDTH)
	{
		if (get_camera(env->buffer[x], &camera, y))
		{
			if (camera.pos.x != old_cam.pos.x || camera.pos.y != old_cam.pos.y)
			{
				precompute_steps(&camera, &floor_step, &floor, y);
				floor.x += floor_step.x * x;
				floor.y += floor_step.y * x;
				old_cam = camera;
			}
			background_pixel(env, floor, (t_v2d_i){x, y}, textures);
		}
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
