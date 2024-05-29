/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/29 14:32:55 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

# include <stdio.h>

inline void	draw_portal(t_img *img, t_hit_buffer *hit_buffer, int x)
{
	t_color			*dst;
	t_color			*end_dst;
	t_color			*tex;
	double			step;
	double			tex_y;
	t_color			color_new;	// test

	dst = (t_color *)img->addr;
	tex = (t_color *)(hit_buffer->texture->addr + (hit_buffer->tex_x << 2));
	tex_y = 0.0;
	step = 1.0 * hit_buffer->texture->height / ((hit_buffer->y2 - hit_buffer->y1) + 1);
	if (hit_buffer->y1 < 0)
	{
		tex_y = -hit_buffer->y1 * step;
		hit_buffer->y1 = 0;
	}
	if (hit_buffer->y2 >= HEIGHT)
		hit_buffer->y2 = HEIGHT - 1;
	dst += ((int)hit_buffer->y1 << WIDTH_LOG2) + x;
	end_dst = dst + ((int)(hit_buffer->y2 - hit_buffer->y1)) * WIDTH;
	while (dst <= end_dst)
	{
		color_new = tex[(int)tex_y * hit_buffer->texture->width];
		if (hit_buffer->side == 1)
		{
			color_new.r *= SHADOW;
			color_new.g *= SHADOW;
			color_new.b *= SHADOW;
		}
		color_new.r = (color_new.r + dst->r) >> 1;
		color_new.g = (color_new.g + dst->g) >> 1;
		color_new.b = (color_new.b + dst->b) >> 1;
		// color_new.r = (color_new.r + dst->r + dst->r + dst->r) >> 2;
		// color_new.g = (color_new.g + dst->g + dst->g + dst->g) >> 2;
		// color_new.b = (color_new.b + dst->b + dst->b + dst->b) >> 2;
		*dst = color_new;
		dst += WIDTH;
		tex_y += step;
	}
}
