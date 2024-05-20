/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/20 13:57:17 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

# include <stdio.h>

inline void	draw_portal(t_img *img, t_hit_buffer *hit_buffer, int x)
{
	unsigned int	*dst;
	unsigned int	*end_dst;
	unsigned int	*tex;
	double			step;
	double			tex_y;
	t_color			color_new;	// test
	t_color			color_old;	// test

	// (void)ray;
	dst = (unsigned int *)img->addr;
	tex = (unsigned int *)(hit_buffer->texture->addr + (hit_buffer->tex_x << 2));
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
		color_old.argb = *dst;
		color_new.argb = tex[(int)tex_y * hit_buffer->texture->width];
		if (hit_buffer->side == 1)
		{
			color_new.r *= 0.75;
			color_new.g *= 0.75;
			color_new.b *= 0.75;
		}
		color_new.r = (color_new.r + color_old.r) / 2;
		color_new.g = (color_new.g + color_old.g) / 2;
		color_new.b = (color_new.b + color_old.b) / 2;
		*dst = color_new.argb;
		// *dst = tex[(int)tex_y * texture->width];
		dst += WIDTH;
		// dst += 1;
		tex_y += step;
	}
}
