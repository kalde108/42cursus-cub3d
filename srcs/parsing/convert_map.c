/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 03:55:39 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 21:47:11 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"

static void	remove_empty_lines(t_vector *map);
static int	get_map_width(t_vector *map);
static int	fill_lines(t_vector *map, int width);
static char	*map_vector_to_array(t_vector *mapvector, t_cubscene *scene);

int	convert_map(t_vector *map, t_cubscene *scene)
{
	remove_empty_lines(map);
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

static void	remove_empty_lines(t_vector *map)
{
	t_vector	*line;

	line = ft_vector_get(map, 0);
	while (line && !line->total)
	{
		ft_vector_delete(map, 0);
		line = ft_vector_get(map, 0);
	}
	line = ft_vector_get(map, map->total - 1);
	while (line && !line->total)
	{
		ft_vector_delete(map, map->total - 1);
		line = ft_vector_get(map, map->total - 1);
	}
}

static char	*map_vector_to_array(t_vector *mapvector, t_cubscene *scene)
{
	char		*maparray;
	t_vector	*line;
	size_t		i;

	maparray = malloc(sizeof(char) * scene->width * scene->height);
	if (!maparray)
		return (NULL);
	i = 0;
	while (i < mapvector->total)
	{
		line = ft_vector_get(mapvector, i);
		ft_memcpy(maparray + (i * scene->width), line->ptr, line->total);
		i++;
	}
	return (maparray);
}
