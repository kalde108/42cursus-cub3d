/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:48:45 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:48:46 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

int	is_on_minimap(t_minimap *minimap, int x, int y)
{
	t_v2d_i	top_left;
	t_v2d_i	bottom_right;

	if (!minimap->enable)
		return (0);
	top_left = (t_v2d_i){minimap->pos.x - (minimap->size >> 1),
		minimap->pos.y - (minimap->size >> 1)};
	bottom_right = (t_v2d_i){minimap->pos.x + (minimap->size >> 1),
		minimap->pos.y + (minimap->size >> 1)};
	return (x >= top_left.x && x <= bottom_right.x
		&& y >= top_left.y && y <= bottom_right.y);
}
