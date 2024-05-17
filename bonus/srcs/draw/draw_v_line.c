/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_v_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 18:08:33 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

# include <stdio.h>

inline void	draw_v_line(t_img *img, t_vline *line, int tex_x, t_texdata *texture, t_ray *ray)
{
	unsigned int	*dst;
	unsigned int	*end_dst;
	unsigned int	*tex;
	double			step;
	double			tex_y;
	t_color			color;	// test

	(void)ray;
	dst = (unsigned int *)img->addr;
	tex = (unsigned int *)(texture->addr + (tex_x << 2));
	tex_y = 0.0;
	step = 1.0 * texture->height / ((line->end - line->start) + 1);
	if (line->start < 0)
	{
		tex_y = -line->start * step;
		line->start = 0;
	}
	if (line->end >= HEIGHT)
		line->end = HEIGHT - 1;
	dst += ((int)line->start << WIDTH_LOG2) + line->x;
	end_dst = dst + ((int)(line->end - line->start)) * WIDTH;
	while (dst <= end_dst)
	{
		color.argb = tex[(int)tex_y * texture->width];
		if (ray->side == 1)
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
