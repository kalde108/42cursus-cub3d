/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cell_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:39:06 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 20:16:00 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "tile_address.h"

static char	get_layer_cell(t_vector *map, int y, int x, int layer);

# include "stdio.h"

int	get_cell_value(t_vector map[LAYERS_COUNT], int y, int x, short *cell)
{
	const char	wall = get_layer_cell(map, y, x, MAP_LAYER) - 'a';
	const char	floor = get_layer_cell(map, y, x, FLOOR_LAYER) - 'a';
	const char	ceiling = get_layer_cell(map, y, x, CEILING_LAYER) - 'a';

	if (WALKABLE == wall && MISSING != floor && MISSING != ceiling)
	{
		*cell = TYPE_FL_CE | floor | (ceiling << CEILING_SHIFT);
		return (0);
	}
	if (WALKABLE == wall)
	{
		//INVALID MAP ERROR MESSAGE
		return (-1); 
	}
	if (PORTAL_CELL == wall)
	{
		*cell = TYPE_PORTAL;
		return (0);
	}
	if (MISSING != wall)
	{
		*cell = TYPE_WALL | wall;
		return (0);
	}
	if (MISSING != floor && MISSING != ceiling)
	{
		*cell = TYPE_FL_CE | floor | (ceiling << CEILING_SHIFT);
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
