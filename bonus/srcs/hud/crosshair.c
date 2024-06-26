/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:49:54 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:49:55 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

static inline void	vbar(t_color *dst, t_v2d_i center, t_v2d_i size)
{
	int		x;
	int		y;
	t_color	color;

	y = center.y - (size.y >> 1);
	while (y < center.y + (size.y >> 1))
	{
		x = center.x - (size.x >> 1);
		while (x < center.x + (size.x >> 1))
		{
			color = dst[(y << WIDTH_LOG2) + x];
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
			dst[(y << WIDTH_LOG2) + x] = color;
			x++;
		}
		y++;
	}
}

static inline void	hbar(t_color *dst, t_v2d_i center, t_v2d_i size)
{
	int		x;
	int		y;
	t_color	color;

	y = center.y - (size.x >> 1);
	while (y < center.y + (size.x >> 1))
	{
		x = center.x - (size.y >> 1);
		while (x < center.x + (size.y >> 1))
		{
			if (x >= center.x - (size.x >> 1)
				&& x <= center.x + (size.x >> 1) - 1)
			{
				x++;
				continue ;
			}
			color = dst[(y << WIDTH_LOG2) + x];
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
			dst[(y << WIDTH_LOG2) + x] = color;
			x++;
		}
		y++;
	}
}

void	crosshair(t_c3_env *env)
{
	t_v2d_i			center;
	t_v2d_i			size;

	center.x = WIDTH >> 1;
	center.y = HEIGHT >> 1;
	size.x = 3;
	size.y = 20;
	vbar(env->img.addr, center, size);
	hbar(env->img.addr, center, size);
}
