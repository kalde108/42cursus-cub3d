/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 03:55:39 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:51 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"
#include "cubdef.h"
#include "tile_address.h"

static int	get_map_width(t_vector *map);
static int	fill_lines(t_vector *map, int width);
static int	*map_vector_to_array(t_vector map[LAYER_COUNT], t_cubscene *scene);
static void	add_portals(t_cubscene *scene);

int	convert_map(t_vector map[LAYER_COUNT], t_cubscene *scene)
{
	scene->height = map->total;
	scene->width = get_map_width(map);
	if (fill_lines(map, scene->width))
		return (1);
	scene->map = map_vector_to_array(map, scene);
	if (!scene->map)
		return (1);
	add_portals(scene);
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

static int	*map_vector_to_array(t_vector map[LAYER_COUNT], t_cubscene *scene)
{
	const size_t	size = scene->width * scene->height;
	int			*s_map;
	size_t			i;

	s_map = malloc(sizeof(int) * size);
	if (!s_map)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (get_cell_value(map, i / scene->width, i % scene->width, s_map + i))
		{
			free(s_map);
			return (NULL);
		}
		i++;
	}
	return (s_map);
}

static void	add_portals(t_cubscene *scene)
{
	int			i;
	t_portal	curr;
	int			curr_index;

	i = 0;
	while (i < scene->portals.total)
	{
		curr = scene->portals.tab[i];
		curr_index = curr.pos.y * scene->width + curr.pos.x;
		scene->map[curr_index] = TYPE_PORTAL | curr.id << PORTAL_SHIFT;
		i++;
	}
}
