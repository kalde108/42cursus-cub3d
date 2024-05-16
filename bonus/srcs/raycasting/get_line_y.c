/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_y.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:26 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/14 16:51:42 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	get_line_y(t_vline *line, double perp_wall_dist)
{
	double	line_height;

	if (perp_wall_dist == 0)
		line_height = HEIGHT;
	else
		line_height = (HEIGHT / perp_wall_dist);
	line->start = -line_height / 2 + HEIGHT / 2;
	line->end = line_height / 2 + HEIGHT / 2;
}
