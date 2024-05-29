/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/29 15:38:48 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "raycasting.h"
#include "tile_address.h"
#include "cub3d.h"
#include "draw.h"

# include <stdio.h>
# include <math.h>
# include "ft_math.h"

void	render_map_chunk(t_c3_env *env, int start, int end)
{
	int				x;
	t_hit_buffer	*hit_buf;
	int				hit_count;

	x = start;
	while (x < end)
	{
		// env->buffer[x];
		hit_count = env->buffer[x]->count;
		// dprintf(2, "hit_count: %d\n", hit_count);
		// dprintf(2, "hit cell: %d\n", env->buffer[x][0].cell);
		while (hit_count-- > 0)
		{
			hit_buf = env->buffer[x] + hit_count;
			if (IS_WALL(hit_buf[hit_count].cell))
				draw_wall(&env->img, hit_buf + hit_count, x);
			else if (IS_PORTAL(hit_buf[hit_count].cell))
				draw_portal(&env->img, hit_buf + hit_count, x);
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
