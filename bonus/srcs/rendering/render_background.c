#include <pthread.h>

#include "cub3d.h"
#include "libft.h"
#include "tile_address.h"
#include "raycasting.h"

# include <stdio.h>

// static inline void	portal_buffer(t_c3_env *env)
// {
// 	t_ray	ray;
// 	// t_vline	line;
// 	// t_texdata	*texture;
// 	// int		tex_x;
// 	int				x;
// 	t_hit_buffer	buffer[MAX_LAYERS];
// 	int				hit_count;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		hit_count = 0;
// 		screen_ray_calculation(&env->player, &ray, x);
// 		while (NOT_WALL(ray.hit_type))
// 		{
// 			ft_dda(&env->scene, &ray);
// 			// if (!hit_count)
// 				// env->z_buffer[x] = ray.perp_wall_dist;
// 			get_line_y(buffer + hit_count, ray.perp_wall_dist);
// 			buffer[hit_count].side = ray.side;
// 			buffer[hit_count].type = ray.hit_type;
// 			hit_count++;
// 		}
// 		// while (hit_count-- > 0)
// 		// {
// 		// 	if (IS_WALL(buffer[hit_count].type))
// 		// 		draw_wall(&env->img, buffer + hit_count, x);
// 		// 	else if (IS_PORTAL(buffer[hit_count].type))
// 		// 		draw_portal(&env->img, buffer + hit_count, x);
// 		// }
		
// 		x++;
// 	}
// }

static inline void	precompute_steps(t_camera *camera, t_v2d_d *floor_step, t_v2d_d *floor, size_t y)
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

static inline int	get_background_color(t_texdata *texture, t_v2d_d floor, t_v2d_i cell_pos, int cell) // cell for debug
{
	t_v2d_i	tex_coord;

	if (!texture)
		dprintf(2, "no texture\n");
	else if ((void *)texture < (void *)100)
		dprintf(2, "texture: %p\n", texture);
	tex_coord.x = (int)(texture->width * (floor.x - cell_pos.x));
	tex_coord.y = (int)(texture->height * (floor.y - cell_pos.y));

	if (!texture->addr)
		dprintf(2, "no addr\ttexture: %p\tfx = %f\tfy = %f\tcx = %d\tcy = %d\tcell: %X\n", texture, floor.x, floor.y, cell_pos.x, cell_pos.y, cell);
	else if ((void *)texture->addr < (void *)100)
		dprintf(2, "addr: %p\ttexture: %p\tx = %d\ty = %d\n", texture->addr, texture, cell_pos.x, cell_pos.y);
	return (((uint32_t *)texture->addr)[texture->width * tex_coord.y + tex_coord.x]);
}

static inline void	background_pixel(t_c3_env *env, t_v2d_d floor, t_v2d_i pixel, t_elem **textures)
{
	t_v2d_i	cell_pos;
	int		cell;

	cell_pos.x = (int)(floor.x);
	cell_pos.y = (int)(floor.y);
	if (cell_pos.x < 0 || cell_pos.x >= env->scene.width || cell_pos.y < 0 || cell_pos.y >= env->scene.height || !IS_FL_CE(env->scene.map[cell_pos.y * env->scene.width + cell_pos.x]))
		return ;
	cell = env->scene.map[cell_pos.y * env->scene.width + cell_pos.x];
	// if (cell_pos.x == 22 && cell_pos.y == 7)
	// 	dprintf(2, "cell: %d\tTYPE: %d\tFLOOR: %d\tCEIL: %d\n", cell, GET_TYPE(cell), GET_FLOOR(cell), GET_CEILING(cell));
	((__uint32_t *)env->img.addr)[pixel.y * WIDTH + pixel.x] = get_background_color(textures[FLOOR][GET_FLOOR(cell)].current, floor, cell_pos, cell);
	((__uint32_t *)env->img.addr)[(HEIGHT - pixel.y - 1) * WIDTH + pixel.x] = get_background_color(textures[CEILING][GET_CEILING(cell)].current, floor, cell_pos, cell);
}

static inline t_camera	get_camera(t_c3_env *env, int x, int y)
{
	int				hit_count;
	int				i;

	hit_count = env->buffer[x]->count;
	i = 0;
	while (i < hit_count)
	{
		if (y <= env->buffer[x][i].y1 || y >= env->buffer[x][i].y2)
			return (env->buffer[x][i].camera);
		i++;
	}
	i--;
	return (env->buffer[x][i].camera);
}

// static inline t_camera	get_camera(t_c3_env *env, int x, int y)
// {
// 	int				hit_count;
// 	t_camera		*camera;

// 	hit_count = env->buffer[x]->count;
// 	// hit_buf = env->buffer[x] + (hit_count - 1);
// 	camera = &env->buffer[x][hit_count - 1].camera;
// 	while (hit_count-- > 0)
// 	{
// 		if (env->buffer[x][hit_count].y1 <= y && env->buffer[x][hit_count].y2 >= y)
// 			return (*camera);
// 		else
// 			camera = &env->buffer[x][hit_count].camera;
// 		// hit_buf--;
// 		hit_count--;
// 	}
// 	return (*camera);
// }

// static inline t_camera	get_camera(t_c3_env *env, int x, int y)
// {
// 	t_hit_buffer	*hit_buf;
// 	int				hit_count;
// 	t_camera		*camera;

// 	hit_count = env->buffer[x]->count;
// 	hit_buf = env->buffer[x] + hit_count;
// 	camera = &hit_buf->camera;
// 	while (hit_count-- > 0)
// 	{
// 		if (hit_buf->y1 <= y && hit_buf->y2 >= y)
// 			return (*camera);
// 		else
// 			camera = &hit_buf->camera;
// 		hit_buf--;
// 		hit_count--;
// 	}
// 	return (*camera);
// }

static inline void	background_row(t_c3_env *env, int y, t_elem **textures)
{
	t_v2d_d 	floor_step;
	t_v2d_d		floor;
	t_camera	old_camera;
	t_camera	camera;
	int			x;

	x = 0;
	old_camera = get_camera(env, x, y);
	precompute_steps(&old_camera, &floor_step, &floor, y);
	while (x < WIDTH)
	{
		camera = get_camera(env, x, y);
		if (camera.pos.x != old_camera.pos.x || camera.pos.y != old_camera.pos.y)
		{
			precompute_steps(&camera, &floor_step, &floor, y);
			floor.x += floor_step.x * x;
			floor.y += floor_step.y * x;
			old_camera = camera;
		}
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
