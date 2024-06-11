/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:12 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

static inline double	get_starting_y(t_hit_buffer *buffer, double step)
{
	double	tex_y;

	tex_y = 0.0;
	if (buffer->y1 < 0)
	{
		tex_y = -buffer->y1 * step;
		buffer->y1 = 0;
	}
	buffer->y2 += 1.0;
	if (buffer->y2 >= HEIGHT)
		buffer->y2 = HEIGHT - 1;
	return (tex_y);
}

static inline void	get_color(t_color tex, int side, t_color *dst)
{
	if (side == 1)
	{
		tex.r *= SHADOW;
		tex.g *= SHADOW;
		tex.b *= SHADOW;
	}
	tex.r = (tex.r + dst->r) >> 1;
	tex.g = (tex.g + dst->g) >> 1;
	tex.b = (tex.b + dst->b) >> 1;
	*dst = tex;
}

inline void	draw_portal(t_img *img, t_hit_buffer *hit_buffer, int x)
{
	t_color			*dst;
	t_color			*end_dst;
	t_color			*tex;
	double			step;
	double			tex_y;

	dst = img->addr;
	tex = hit_buffer->texture->addr + hit_buffer->tex_x;
	step = 1.0 * hit_buffer->texture->height
		/ ((hit_buffer->y2 - hit_buffer->y1) + 1);
	tex_y = get_starting_y(hit_buffer, step);
	dst += ((int)hit_buffer->y1 << WIDTH_LOG2) + x;
	end_dst = dst + ((int)(hit_buffer->y2 - hit_buffer->y1)) * WIDTH;
	while (dst <= end_dst)
	{
		get_color(tex[(int)tex_y * hit_buffer->texture->width],
			hit_buffer->side,
			dst);
		dst += WIDTH;
		tex_y += step;
	}
}
