/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cell_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:39:06 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 17:42:21 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "tile_address.h"

# include <stdio.h> 

static char	get_layer_cell(t_vector *map, int y, int x, int layer);

int	get_cell_value(t_vector map[LAYERS_COUNT], int y, int x, short *cell)
{
	const char	wall = get_layer_cell(map, y, x, MAP_LAYER);
	const char	floor = get_layer_cell(map, y, x, FLOOR_LAYER);
	const char	ceiling = get_layer_cell(map, y, x, CEILING_LAYER);

	if ('.' == wall)
	{
		if (floor && ceiling)
		{
			*cell = TYPE_FL_CE | floor - 'a' | (ceiling - 'a') << CEILING_SHIFT;
			return (0);
		}
		else
			return (-1); //map invalide
	}
	if (wall)
	{
		*cell = TYPE_WALL | wall - 'a';
		return (0);
	}
	if (floor && ceiling)
	{
		*cell = TYPE_FL_CE | floor - 'a' | (ceiling - 'a') << CEILING_SHIFT;
		return (0);
	}
	*cell = EMPTY_CELL;
	return (0);
}

static char	get_layer_cell(t_vector *map, int y, int x, int layer)
{
	t_vector	*line;
	char		*cell;

	line = ft_vector_get(map + layer, y);
	if (NULL != line)
	{
		cell = ft_vector_get(line, x);
		if (cell && ' ' != *cell)
			return (*cell);
		return ('\0');
	}
	else
		return ('\0');
}
