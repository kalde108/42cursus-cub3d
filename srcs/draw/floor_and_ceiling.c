/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:15 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:54:36 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	draw_ceiling(t_c3_env *env)
{
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
		img_ptr[cursor] = color;
	}
}

static inline void	draw_floor(t_c3_env *env)
{
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
		img_ptr[cursor] = color;
	}
}

void	floor_and_ceiling(t_c3_env *env)
{
	draw_ceiling(env);
	draw_floor(env);
}
