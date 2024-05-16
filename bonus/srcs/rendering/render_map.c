/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 19:20:04 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "raycasting.h"
#include "tile_address.h"

# include <stdio.h>

void	render_map_chunk(t_c3_env *env, int start, int end)
{
	t_ray	ray;
	t_vline	line;
	t_texdata	*texture;
	int		tex_x;

	line.x = start;
	while (line.x < end)
	{
		ray_calculation(&env->player, &ray, line.x);
		ft_dda(&env->scene, &ray);
		env->z_buffer[line.x] = ray.perp_wall_dist;
		texture = get_wall_texture(&env->scene, ray.map_pos, env->scene.elems);
		tex_x = get_tex_x(&ray, texture->width, env->player);
		get_line_y(&line, ray.perp_wall_dist);
		draw_v_line(&env->img, &line, tex_x, texture, &ray);
		line.x++;
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
