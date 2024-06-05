/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/05 16:36:44 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

# include <stdio.h>

inline void	draw_wall(t_img *img, t_hit_buffer *hit_buffer, int x)
{
	t_color	*dst;
	t_color	*end_dst;
	t_color	*tex;
	double			step;
	double			tex_y;

	dst = img->addr;
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
		*dst = tex[(int)tex_y * hit_buffer->texture->width];
		if (hit_buffer->side == 1)
		{
			dst->r *= SHADOW;
			dst->g *= SHADOW;
			dst->b *= SHADOW;
		}
		dst += WIDTH;
		tex_y += step;
	}
}
