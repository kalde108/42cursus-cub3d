/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cell_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:39:06 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/10 23:58:53 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static char	get_layer_cell(t_vector *map, int x, int y);

short	get_cell_value(t_vector map[LAYERS_COUNT], int x, int y)
{
	const char	floor_cell = get_layer_cell(map, x, y, FLOOR_LAYER);
	const char	ceiling_cell = get_layer_cell(map, x, y, CEILING_LAYER);

	if ('\0' == floor_cell || '\0' == ceiling_cell)
		return (1);

}

static char	get_layer_cell(t_vector *map, int x, int y, int layer)
{
	t_vector	*line;
	char		*cell;

	line = ft_vector_get(map + layer, y);
	if (NULL != line)
		cell = ft_vector_get(line, x);
	else
		cell = '\0';
	if ('\0' == cell)
	{
		if (FLOOR_LAYER == layer)
			; //ERROR MSG
		else
			; //ERROR MSG
	}
	return (*cell);
}
