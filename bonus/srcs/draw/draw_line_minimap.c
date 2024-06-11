/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:47:25 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:26 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minimap.h"

static void	draw_line_low(t_c3_env *env, t_v2d_i p1, t_v2d_i p2, t_color color)
{
	t_v2d_i	delta;
	int		yi;
	int		d;

	delta = (t_v2d_i){p2.x - p1.x, p2.y - p1.y};
	yi = 1;
	if (delta.y < 0)
	{
		yi = -1;
		delta.y = -delta.y;
	}
	d = 2 * delta.y - delta.x;
	while (p1.x <= p2.x)
	{
		if (is_on_minimap(&env->options.minimap, p1.x, p1.y))
			env->img.addr[(p1.y << WIDTH_LOG2) + p1.x] = color;
		if (d > 0)
		{
			p1.y += yi;
			d -= 2 * delta.x;
		}
		d += 2 * delta.y;
		p1.x++;
	}
}

static void	draw_line_high(t_c3_env *env, t_v2d_i p1, t_v2d_i p2, t_color color)
{
	t_v2d_i	delta;
	int		xi;
	int		d;

	delta = (t_v2d_i){p2.x - p1.x, p2.y - p1.y};
	xi = 1;
	if (delta.x < 0)
	{
		xi = -1;
		delta.x = -delta.x;
	}
	d = 2 * delta.x - delta.y;
	while (p1.y <= p2.y)
	{
		if (is_on_minimap(&env->options.minimap, p1.x, p1.y))
			env->img.addr[(p1.y << WIDTH_LOG2) + p1.x] = color;
		if (d > 0)
		{
			p1.x += xi;
			d -= 2 * delta.y;
		}
		d += 2 * delta.x;
		p1.y++;
	}
}

void	draw_line_minimap(t_c3_env *env, t_v2d_i p1, t_v2d_i p2, t_color color)
{
	int	dx;
	int	dy;

	if (p2.x - p1.x >= 0)
		dx = p2.x - p1.x;
	else
		dx = p1.x - p2.x;
	if (p2.y - p1.y >= 0)
		dy = p2.y - p1.y;
	else
		dy = p1.y - p2.y;
	if (dy < dx)
	{
		if (p1.x > p2.x)
			draw_line_low(env, p2, p1, color);
		else
			draw_line_low(env, p1, p2, color);
	}
	else
	{
		if (p1.y > p2.y)
			draw_line_high(env, p2, p1, color);
		else
			draw_line_high(env, p1, p2, color);
	}
}
