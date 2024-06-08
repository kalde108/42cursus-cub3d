/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/08 18:19:08 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static double	get_starting_y(t_hit_buffer *buffer, double step);

inline void	draw_wall(t_img *img, t_hit_buffer *buffer, int x)
{
	t_color	*dst;
	t_color	*end_dst;
	t_color	*tex;
	double	step;
	double	tex_y;

	dst = img->addr;
	tex = buffer->texture->addr + (buffer->tex_x);
	step = 1.0 * buffer->texture->height / ((buffer->y2 - buffer->y1) + 1);
	tex_y = get_starting_y(buffer, step);
	dst += ((int)buffer->y1 << WIDTH_LOG2) + x;
	end_dst = dst + ((int)(buffer->y2 - buffer->y1)) * WIDTH;
	while (dst <= end_dst)
	{
		*dst = tex[(int)tex_y * buffer->texture->width];
		if (buffer->side == 1)
		{
			dst->r *= SHADOW;
			dst->g *= SHADOW;
			dst->b *= SHADOW;
		}
		dst += WIDTH;
		tex_y += step;
	}
}

static double	get_starting_y(t_hit_buffer *buffer, double step)
{
	double	tex_y;

	tex_y = 0.0;
	if (buffer->y1 < 0)
	{
		tex_y = -buffer->y1 * step;
		buffer->y1 = 0;
	}
	if (buffer->y2 >= HEIGHT)
		buffer->y2 = HEIGHT - 1;
	return (tex_y);
}
