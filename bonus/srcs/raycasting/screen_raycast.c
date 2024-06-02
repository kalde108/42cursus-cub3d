#include <pthread.h>

#include "cub3d.h"
#include "tile_address.h"

# include "draw.h"

void	raycast_chunk(t_c3_env *env, int start, int end)
{
	t_ray			ray;
	int				x;
	int				hit_count;
	t_camera		tmp_camera;
	t_hit_buffer	*hit_buf;

	x = start;
	while (x < end)
	{
		hit_count = 0;
		ray.total_perp_wall_dist = 0;
		ray.hit_type = 0;
		tmp_camera.pos = env->player.pos;
		tmp_camera.dir = env->player.dir;
		tmp_camera.plane = env->player.plane;
		while ((NOT_WALL(ray.hit_type) && !(IS_PORTAL(ray.hit_type) && -1 == env->scene.portals.tab[GET_PORTAL(ray.hit_type)].linked_portal)) && hit_count < MAX_LAYERS)
		{
			if (IS_PORTAL(ray.hit_type))
				portal_hit(&env->scene, &ray, &tmp_camera);
			screen_ray_calculation(&tmp_camera, &ray, x);
			ft_dda(&env->scene, &ray);
			hit_buf = env->buffer[x] + hit_count;
			hit_buf->side = ray.side;
			hit_buf->cell = ray.hit_type;
			hit_buf->z = ray.perp_wall_dist;
			hit_buf->texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
			hit_buf->tex_x = get_tex_x(&ray, hit_buf->texture->width, &tmp_camera);
			get_line_y(hit_buf, ray.perp_wall_dist);
			hit_buf->camera = tmp_camera;
			hit_count++;
		}
		env->buffer[x]->count = hit_count;
		x++;
	}
}

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

int	screen_raycast(t_c3_env *env)
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
