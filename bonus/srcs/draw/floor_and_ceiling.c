/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:15 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 15:43:23 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static inline void	draw_ceiling(t_c3_env *env)
// {
// 	register int			cursor;
// 	static const int		max = (HEIGHT * (WIDTH >> 2)) >> 1;
// 	__int128_t				*img_ptr;
// 	const __int128_t		color = ((__int128_t)env->scene.ceiling << 96) + \
// 								((__int128_t)env->scene.ceiling << 64) + \
// 								((__int128_t)env->scene.ceiling << 32) + \
// 								((__int128_t)env->scene.ceiling);

// 	img_ptr = (__int128_t *)env->img.addr;
// 	cursor = -1;
// 	while (++cursor < max)
// 	{
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor] = color;
// 	}
// }

// static inline void	draw_floor(t_c3_env *env)
// {
// 	register int			cursor;
// 	static const int		max = (HEIGHT * (WIDTH >> 2));
// 	__int128_t				*img_ptr;
// 	const __int128_t		color = ((__int128_t)env->scene.floor << 96) + \
// 								((__int128_t)env->scene.floor << 64) + \
// 								((__int128_t)env->scene.floor << 32) + \
// 								((__int128_t)env->scene.floor);

// 	img_ptr = (__int128_t *)env->img.addr;
// 	cursor = ((HEIGHT * (WIDTH >> 2)) >> 1) - 1;
// 	while (++cursor < max)
// 	{
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor] = color;
// 	}
// }

static void	draw_floor(t_c3_env *env)
{
	size_t		y;
	const size_t		half_h = HEIGHT / 2;
	t_tex				*floor_tex = &env->scene.texture[FL];
	t_tex				*ceiling_tex = &env->scene.texture[CE];

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		float	ray_dirx0 = env->player.dir.x - env->player.plane.x;
		float	ray_diry0 = env->player.dir.y - env->player.plane.y;
		float	ray_dirx1 = env->player.dir.x + env->player.plane.x;
		float	ray_diry1 = env->player.dir.y + env->player.plane.y;

		int		p = y - half_h;

		float	posz = 0.5 * HEIGHT;

		float	row_distance = posz / p;

		float	floor_step_x = row_distance * (ray_dirx1 - ray_dirx0) / WIDTH;
		float	floor_step_y = row_distance * (ray_diry1 - ray_diry0) / WIDTH;

		float	floor_x = env->player.pos.x + row_distance * ray_dirx0;
		float	floor_y = env->player.pos.y + row_distance * ray_diry0;

		size_t	x = 0;
		while (x < WIDTH)
		{
			int		cell_x = (int)(floor_x);
			int		cell_y = (int)(floor_y);

			int		f_tx = (int)(floor_tex->width * (floor_x - cell_x)) & (floor_tex->width - 1);
			int		f_ty = (int)(floor_tex->height * (floor_y - cell_y)) & (floor_tex->height - 1);

			int		c_tx = (int)(ceiling_tex->width * (floor_x - cell_x)) & (ceiling_tex->width - 1);
			int		c_ty = (int)(ceiling_tex->height * (floor_y - cell_y)) & (ceiling_tex->height - 1);

			floor_x += floor_step_x;
			floor_y += floor_step_y;

			// *((__uint32_t *)env->img.addr + (y << 11) + x) = color;
			__uint32_t	color = ((uint32_t *)floor_tex->addr)[floor_tex->width * f_ty + f_tx];
			((__uint32_t *)env->img.addr)[y * WIDTH + x] = color;

			color =  ((uint32_t *)ceiling_tex->addr)[ceiling_tex->width * c_ty + c_tx];
			((__uint32_t *)env->img.addr)[(HEIGHT - y - 1) * WIDTH + x] = color;

			x++;
		}
		y++;
	}
}

void	floor_and_ceiling(t_c3_env *env)
{
	// draw_ceiling(env);
	draw_floor(env);
}
