/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cell_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:39:06 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/12 16:09:44 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parsing.h"
#include "tile_address.h"

static char	get_layer_cell(t_vector *map, int y, int x, int layer);
static char	*cell_error(char floor, char ceiling);

int	get_cell_value(t_vector map[LAYER_COUNT], int y, int x, int *cell)
{
	const char	wall = get_layer_cell(map, y, x, MAP_LAYER) - 'a';
	const char	floor = get_layer_cell(map, y, x, FLOOR_LAYER) - 'a';
	const char	ceiling = get_layer_cell(map, y, x, CEILING_LAYER) - 'a';

	if (MISSING == wall || PORTAL_CELL == wall)
		*cell = EMPTY_CELL;
	else if (wall >= 0 && wall < 26)
		*cell = TYPE_WALL | wall;
	else if (MISSING != floor && MISSING != ceiling)
		*cell = TYPE_FL_CE | floor | (ceiling << CEILING_SHIFT);
	else
	{
		ft_dprintf(STDERR_FILENO, INVAL_CELL, x, y, cell_error(floor, ceiling));
		return (-1);
	}
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
		if (cell && ' ' != *cell && - 'P' != *cell)
			return (*cell);
		return ('\0');
	}
	else
		return ('\0');
}

static char	*cell_error(char floor, char ceiling)
{
	if (MISSING == floor && MISSING == ceiling)
		return (MISSING_FLOOR_CEILING);
	if (MISSING == floor)
		return (MISSING_FLOOR);
	return (MISSING_CEILING);
}
