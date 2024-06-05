/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/05 15:33:31 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "cub3d.h"
#include "raycasting.h"
#include "tile_address.h"
#include "draw.h"

void	render_map_chunk(t_c3_env *env, int start, int end)
{
	int				x;
	int				hit_count;
	t_hit_buffer	*hit_buf;
	t_portals		*portals;

	portals = &env->scene.portals;
	x = start;
	while (x < end)
	{
		hit_count = env->buffer[x]->count;
		while (hit_count-- > 0)
		{
			hit_buf = env->buffer[x] + hit_count;
			if (IS_WALL(hit_buf->cell) || (IS_PORTAL(hit_buf->cell) && -1 \
					== portals->tab[GET_PORTAL(hit_buf->cell)].linked_portal))
				draw_wall(&env->img, hit_buf, x);
			else if (IS_PORTAL(hit_buf->cell))
				draw_portal(&env->img, hit_buf, x);
		}
		x++;
	}
}

void	*render_map_thread(void *arg)
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
	render_map_chunk(env, start, end);
	return (NULL);
}

int	render_map(t_c3_env *env)
{
	pthread_t	threads[CPUCORES];
	int			i;
	int			err;

	err = 0;
	i = 0;
	while (i < CPUCORES)
	{
		err = pthread_create(&threads[i], NULL, render_map_thread, env);
		if (err)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	return (err);
}
