/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:15 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 15:58:01 by kchillon         ###   ########lyon.fr   */
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

static void	draw_floor_ceiling(t_c3_env *env)
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

		t_v2d_d floor_step;
		floor_step.x = row_distance * (ray_dirx1 - ray_dirx0) / WIDTH;
		floor_step.y = row_distance * (ray_diry1 - ray_diry0) / WIDTH;

		t_v2d_d	floor;
		floor.x = env->player.pos.x + row_distance * ray_dirx0;
		floor.y = env->player.pos.y + row_distance * ray_diry0;

		size_t	x = 0;
		while (x < WIDTH)
		{
			t_v2d_i	cell;

			cell.x = (int)(floor.x);
			cell.y = (int)(floor.y);

			if (cell.x < 0 || cell.x >= env->scene.width || cell.y < 0 || cell.y >= env->scene.height || env->scene.map[cell.y * env->scene.width + cell.x] != '0')
			{
				x++;
				floor.x += floor_step.x;
				floor.y += floor_step.y;
				continue ;
			}

			t_v2d_i	floor_coord;
			floor_coord.x = (int)(floor_tex->width * (floor.x - cell.x)) & (floor_tex->width - 1);
			floor_coord.y = (int)(floor_tex->height * (floor.y - cell.y)) & (floor_tex->height - 1);

			t_v2d_i	ceiling_coord;
			ceiling_coord.x = (int)(ceiling_tex->width * (floor.x - cell.x)) & (ceiling_tex->width - 1);
			ceiling_coord.y = (int)(ceiling_tex->height * (floor.y - cell.y)) & (ceiling_tex->height - 1);

			floor.x += floor_step.x;
			floor.y += floor_step.y;

			__uint32_t	color = ((uint32_t *)floor_tex->addr)[floor_tex->width * floor_coord.y + floor_coord.x];
			((__uint32_t *)env->img.addr)[y * WIDTH + x] = color;

			color =  ((uint32_t *)ceiling_tex->addr)[ceiling_tex->width * ceiling_coord.y + ceiling_coord.x];
			((__uint32_t *)env->img.addr)[(HEIGHT - y - 1) * WIDTH + x] = color;

			x++;
		}
		y++;
	}
}

void	floor_and_ceiling(t_c3_env *env)
{
	// draw_ceiling(env);
	draw_floor_ceiling(env);
}
