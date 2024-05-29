#include <pthread.h>

#include "cub3d.h"
#include "tile_address.h"

# include "draw.h"

void	raycast_chunk(t_c3_env *env, int start, int end)
{
	t_ray	ray;
	int				x;
	int				hit_count;

	x = start;
	while (x < end)
	{
		hit_count = 0;
		ray.total_perp_wall_dist = 0;
		ray.hit_type = 0;
		env->buffer[x][hit_count].camera.pos = env->player.pos;
		env->buffer[x][hit_count].camera.dir = env->player.dir;
		env->buffer[x][hit_count].camera.plane = env->player.plane;
		while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
		{
			if (IS_PORTAL(ray.hit_type))
				portal_hit(&env->scene, &ray, &env->buffer[x][hit_count].camera);
			ray_calculation(&env->buffer[x][hit_count].camera, &ray, x);
			ft_dda(&env->scene, &ray);
			env->buffer[x][hit_count].side = ray.side;
			env->buffer[x][hit_count].cell = ray.hit_type;
			env->buffer[x][hit_count].z = ray.perp_wall_dist;
			env->buffer[x][hit_count].texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
			env->buffer[x][hit_count].tex_x = get_tex_x(&ray, env->buffer[x][hit_count].texture->width, &env->buffer[x][hit_count].camera);
			get_line_y(env->buffer[x] + hit_count, ray.perp_wall_dist);
			hit_count++;
		}
		env->buffer[x]->count = hit_count;
		x++;
	}
}

// void	raycast_chunk(t_c3_env *env, int start, int end)
// {
// 	t_ray	ray;
// 	t_hit_buffer	*hit_buff;
// 	int				x;
// 	int				hit_count;

// 	x = start;
// 	while (x < end)
// 	{
// 		hit_count = 0;
// 		ray.total_perp_wall_dist = 0;
// 		ray.hit_type = 0;
// 		env->buffer[x][hit_count].camera.pos = env->player.pos;
// 		env->buffer[x][hit_count].camera.dir = env->player.dir;
// 		env->buffer[x][hit_count].camera.plane = env->player.plane;
// 		while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
// 		{
// 			hit_buff = env->buffer[x] + hit_count;
// 			if (IS_PORTAL(ray.hit_type))
// 				portal_hit(&env->scene, &ray, &hit_buff->camera);
// 			ray_calculation(&hit_buff->camera, &ray, x);
// 			ft_dda(&env->scene, &ray);
// 			hit_buff->side = ray.side;
// 			hit_buff->cell = ray.hit_type;
// 			hit_buff->z = ray.perp_wall_dist;
// 			hit_buff->texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
// 			hit_buff->tex_x = get_tex_x(&ray, hit_buff->texture->width, &hit_buff->camera);
// 			get_line_y(env->buffer[x] + hit_count, ray.perp_wall_dist);
// 			hit_count++;
// 			hit_buff->count = hit_count;
// 		}
// 		x++;
// 	}
// }

void	*raycast_thread(void *arg)
{
	static int	call = 0;
	t_c3_env	*env;
	int			start;
	int			end;

	env = (t_c3_env *)arg;
	pthread_mutex_lock(&env->call_mutex);
	call++;
	call = call % CPUCORES;
	start = call * (WIDTH / CPUCORES);
	end = (call + 1) * (WIDTH / CPUCORES);
	pthread_mutex_unlock(&env->call_mutex);
	raycast_chunk(env, start, end);
	return (NULL);
}

int	raycast(t_c3_env *env)
{
	pthread_t	threads[CPUCORES];
	int			i;
	int			err;

	err = 0;
	i = 0;
	while (i < CPUCORES)
	{
		err = pthread_create(&threads[i], NULL, raycast_thread, env);
		if (err)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	return (err);
}

