/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cell_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:39:06 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 16:41:33 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "tile_address.h"

static char	get_layer_cell(t_vector *map, int x, int y, int layer);

short	get_cell_value(t_vector map[LAYERS_COUNT], int x, int y)
{
	const char	wall_cell = get_layer_cell(map, x, y, MAP_LAYER);
	const char	floor_cell = get_layer_cell(map, x, y, FLOOR_LAYER);
	const char	ceiling_cell = get_layer_cell(map, x, y, CEILING_LAYER);

	if (wall_cell)
		return (TYPE_WALL | wall_cell - 'a');
	// if ('\0' == floor_cell || '\0' == ceiling_cell)
	// 	return (-1);
	return (TYPE_FL_CE | floor_cell - 'a' | (ceiling_cell - 'a') << CEILING_SHIFT);
}

static char	get_layer_cell(t_vector *map, int x, int y, int layer)
{
	t_vector	*line;
	char		*cell;

	line = ft_vector_get(map + layer, y);
	if (NULL != line)
		cell = ft_vector_get(line, x);
	else
		cell = "\0";
	if ('\0' == *cell)
	{
		if (FLOOR_LAYER == layer)
			; //ERROR MSG
		else
			; //ERROR MSG
	}
	return (*cell);
}
