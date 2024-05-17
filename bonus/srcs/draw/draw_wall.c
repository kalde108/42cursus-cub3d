/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 19:58:32 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

# include <stdio.h>

inline void	draw_wall(t_img *img, t_hit_buffer *hit_buffer, int x)
{
	unsigned int	*dst;
	unsigned int	*end_dst;
	unsigned int	*tex;
	double			step;
	double			tex_y;
	t_color			color;	// test

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
		color.argb = tex[(int)tex_y * hit_buffer->texture->width];
		if (hit_buffer->side == 1)
		{
			color.r *= 0.75;
			color.g *= 0.75;
			color.b *= 0.75;
		}
		*dst = color.argb;
		// *dst = tex[(int)tex_y * texture->width];
		dst += WIDTH;
		// dst += 1;
		tex_y += step;
	}
}
