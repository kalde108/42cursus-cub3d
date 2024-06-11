/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tile_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:48:41 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 17:40:46 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "tile_address.h"

t_color	get_tile_color(t_cubscene *scene, int cell)
{
	t_color	color;

	if (cell & TYPE_WALL)
		color = scene->elems[WALL][cell & WALL_MASK].current->average_color;
	else if (cell & TYPE_PORTAL)
	{
		if (scene->portals.tab[(cell & PORTAL_MASK) >> PORTAL_SHIFT].is_open)
			color = scene->elems[PORTAL]->current->average_color;
		else
			color = scene->elems[PORTAL]->frames->average_color;
	}
	else if (cell & TYPE_FL_CE)
		color = scene->elems[FLOOR][cell & FLOOR_MASK].current->average_color;
	else
		color.argb = 0x7F000000;
	return (color);
}
