/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:26 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/16 16:49:44 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "cub3d.h"
#include "tile_address.h"

static inline int	not_linked_portal(t_ray *ray, t_portals *portals)
{
	return (ray->cell & TYPE_PORTAL
		&& NO_LINK == portals->tab[(ray->cell & PORTAL_MASK) \
		>> PORTAL_SHIFT].linked_portal);
}

static void	x_cast(t_cubscene *scene,
					t_hit_buffer *buffer,
					t_camera camera, int x)
{
	t_ray			ray;
	int				hit_count;
	t_hit_buffer	*ptr;

	hit_count = 0;
	ray = (t_ray){0};
	while (((ray.cell & TYPE_MASK) ^ TYPE_WALL
			&& !not_linked_portal(&ray, &scene->portals))
		&& hit_count < MAX_LAYERS)
	{
		if (ray.cell & TYPE_PORTAL)
			portal_hit(scene, &ray, &camera);
		screen_ray_calculation(&camera, &ray, x);
		ft_dda(scene, &ray);
		ptr = buffer + hit_count;
		ptr->side = ray.side;
		ptr->cell = ray.cell;
		ptr->z = ray.perp_wall_dist;
		ptr->texture = get_wall_texture(scene, ray.cell, scene->elems);
		ptr->tex_x = get_tex_x(&ray, ptr->texture->width, &camera);
		get_line_y(ptr, ray.perp_wall_dist);
		ptr->camera = camera;
		hit_count++;
	}
	buffer->count = hit_count;
}

static void	raycast_chunk(t_c3_env *env, int start, int end)
{
	int	x;

	x = start;
	while (x < end)
	{
		x_cast(&env->scene, env->buffer[x], env->player.camera, x);
		x++;
	}
}

static void	*raycast_thread(void *arg)
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
