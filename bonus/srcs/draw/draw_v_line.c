/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_v_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 20:01:12 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

# include <stdio.h>

inline void	draw_v_line(t_img *img, t_vline *line, int tex_x, t_texdata *texture)
{
	unsigned int	*dst;
	unsigned int	*end_dst;
	unsigned int	*tex;
	double			step;
	double			tex_y;

	dst = (unsigned int *)img->addr;
	tex = (unsigned int *)(texture->addr + (tex_x << 2));
	tex_y = 0.0;
	step = 1.0 * texture->height / (line->end - line->start);
	if (line->start < 0)
	{
		tex_y = -line->start * step;
		line->start = 0;
	}
	if (line->end >= HEIGHT)
		line->end = HEIGHT - 1;
	dst += (line->start << WIDTH_LOG2) + line->x;
	end_dst = dst + (line->end - line->start) * WIDTH;
	while (dst <= end_dst)
	{
		*dst = tex[(int)tex_y * texture->width];
		dst += WIDTH;
		tex_y += step;
	}
}
