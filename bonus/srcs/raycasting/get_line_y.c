/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_y.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:26 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 19:31:02 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "raycasting.h"

void	get_line_y(t_hit_buffer *hit_buff, double perp_wall_dist)
{
	double	line_height;

	if (perp_wall_dist == 0)
		line_height = HEIGHT;
	else
		line_height = (HEIGHT / perp_wall_dist);
	hit_buff->y1 = -line_height / 2 + HEIGHT / 2;
	hit_buff->y2 = line_height / 2 + HEIGHT / 2;
}
