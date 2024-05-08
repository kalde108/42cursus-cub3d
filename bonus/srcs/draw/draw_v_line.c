/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_v_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:54:16 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

inline void	draw_v_line(t_img *img, t_vline *line, int tex_x, t_tex *texture)
{
	int				y;
	unsigned int	*dst;
	double			step;
	double			tex_y;

	dst = (unsigned int *)img->addr;
	tex_y = 0.0;
	step = 1.0 * texture->height / (line->end - line->start);
	if (line->start < 0)
	{
		tex_y = -line->start * step;
		line->start = 0;
	}
	if (line->end >= HEIGHT)
		line->end = HEIGHT - 1;
	y = line->start;
	while (y <= line->end)
	{
		dst[(y++ << 11) + line->x] = *(unsigned int *)(texture->addr + \
									(((int)tex_y * texture->line_length) + \
										tex_x * (texture->bits_per_pixel / 8)));
		tex_y += step;
	}
}
