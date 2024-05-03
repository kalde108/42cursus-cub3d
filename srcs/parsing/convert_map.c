/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 03:55:39 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 18:35:23 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern char		**test_map; //REMOVE

static int	get_map_width(t_vector *map);
static int	fill_lines(t_vector *map, int width);

static void	DEBUG_GLOBAL_MAP(t_vector *map); //REMOVE

int	convert_map(t_vector *map)
{
	const int	width = get_map_width(map);

	if (fill_lines(map, width))
		return (1);
	DEBUG_GLOBAL_MAP(map); //REMOVE
	return (0);
}

static int	get_map_width(t_vector *map)
{
	t_vector	*line;
	int			i;
	int			width;

	width = 0;
	i = 0;
	line = ft_vector_get(map, i++);
	while (line)
	{
		if (line->total > (size_t)width)
			width = line->total;
		line = ft_vector_get(map, i++);
	}
	return (width);
}

static int	fill_lines(t_vector *map, int width)
{
	t_vector	*line;
	int			i;

	i = 0;
	line = ft_vector_get(map, i++);
	while (line)
	{
		while (line->total < (size_t)width)
		{
			if (ft_vector_add(line, " "))
			{
				//ERROR MESSAGE
				return (1);
			}
		}
		if (ft_vector_add(line, "\0"))	//SHOULD BE REMOVE WITH FUTURE DATA STRUCTURE
			return (1);					//SHOULD BE REMOVE WITH FUTURE DATA STRUCTURE
		line = ft_vector_get(map, i++);
	}
	return (0);
}

#include <stdio.h>
#include <stdlib.h>

static void	DEBUG_GLOBAL_MAP(t_vector *map)
{
	test_map = malloc(sizeof(char *) * (map->total + 1));
	size_t i = 0;
	while (i < map->total)
	{
		test_map[i] = ((t_vector *)ft_vector_get(map, i))->ptr;
		i++;
	}
	test_map[i] = NULL;
}
