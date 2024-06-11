/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_y.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:26 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:51:28 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	get_line_y(t_vline *line, double perp_wall_dist)
{
	int	line_height;

	if (perp_wall_dist == 0)
		line_height = HEIGHT;
	else
		line_height = (int)(HEIGHT / perp_wall_dist);
	line->start = -line_height / 2 + HEIGHT / 2;
	line->end = line_height / 2 + HEIGHT / 2;
}
