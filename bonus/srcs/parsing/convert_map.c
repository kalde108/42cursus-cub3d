/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 03:55:39 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 16:57:34 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"

static int		get_map_width(t_vector *map);
static int		fill_lines(t_vector *map, int width);
static short	*map_vector_to_array(t_vector map[LAYERS_COUNT], t_cubscene *scene);

int	convert_map(t_vector map[LAYERS_COUNT], t_cubscene *scene)
{
	scene->height = map->total;
	scene->width = get_map_width(map);
	if (fill_lines(map, scene->width))
		return (1);
	scene->map = map_vector_to_array(map, scene);
	if (!scene->map)
		return (1);
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
				ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
				return (1);
			}
		}
		line = ft_vector_get(map, i++);
	}
	return (0);
}

static short	*map_vector_to_array(t_vector map[LAYERS_COUNT], t_cubscene *scene)
{
	const size_t	size = scene->width * scene->height;
	short		*maparray;
	size_t		i;

	maparray = malloc(sizeof(short) * size);
	if (!maparray)
		return (NULL);
	i = 0;
	while (i < size)
	{
		maparray[i] = get_cell_value(map, i / scene->width, i % scene->width);
		i++;
	}
	return (maparray);
}

