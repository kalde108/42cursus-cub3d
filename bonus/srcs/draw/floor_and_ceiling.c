/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:15 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 19:23:20 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <pthread.h>

static void	*draw_ceiling(void *arg)
{
	t_c3_env				*env = arg;
	register int			cursor;
	static const int		max = (HEIGHT * (WIDTH >> 2)) >> 1;
	__int128_t				*img_ptr;
	const __int128_t		color = ((__int128_t)env->scene.ceiling << 96) + \
								((__int128_t)env->scene.ceiling << 64) + \
								((__int128_t)env->scene.ceiling << 32) + \
								((__int128_t)env->scene.ceiling);

	img_ptr = (__int128_t *)env->img.addr;
	cursor = -1;
	while (++cursor < max)
	{
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor] = color;
	}
	return (NULL);
}

static void	*draw_floor(void *arg)
{
	t_c3_env				*env = arg;
	register int			cursor;
	static const int		max = (HEIGHT * (WIDTH >> 2));
	__int128_t				*img_ptr;
	const __int128_t		color = ((__int128_t)env->scene.floor << 96) + \
								((__int128_t)env->scene.floor << 64) + \
								((__int128_t)env->scene.floor << 32) + \
								((__int128_t)env->scene.floor);

	img_ptr = (__int128_t *)env->img.addr;
	cursor = ((HEIGHT * (WIDTH >> 2)) >> 1) - 1;
	while (++cursor < max)
	{
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor] = color;
	}
	return (NULL);
}

void	floor_and_ceiling(t_c3_env *env)
{
	pthread_t	thread_ceiling;
	pthread_t	thread_floor;

	// draw_ceiling(env);
	// draw_floor(env);
	if (pthread_create(&thread_ceiling, NULL, &draw_ceiling, env))
		return ;
	if (pthread_create(&thread_floor, NULL, &draw_floor, env))
		return ;
	pthread_join(thread_ceiling, NULL);
	pthread_join(thread_floor, NULL);
}
