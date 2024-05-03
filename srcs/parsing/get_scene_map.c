/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:25:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 21:18:58 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing.h"

static int	read_map_file(int fd, t_vector *map);
static int	add_map_line(char *str, t_vector *map);
static int	is_line_valid(char *str);

int	get_scene_map(int fd, t_cubscene *scene)
{
	t_vector	map;
	int			status;

	if (ft_vector_init(&map, (t_vinfos){sizeof(t_vector), 0, ft_vvector_free}))
		return (1);
	status = read_map_file(fd, &map);
	if (!status)
		convert_map(&map, scene);
	ft_vector_free(&map);
	return (status);
}

static int	read_map_file(int fd, t_vector *map)
{
	char	*gnl;
	int		status;

	errno = 0;
	status = 0;
	while (!status && !get_next_line(fd, &gnl) && gnl)
	{
		ft_replace_char(gnl, '\n', '\0');
		if (is_line_valid(gnl))
			status = add_map_line(gnl, map);
		else
			status = -1;
		free(gnl);
	}
	return (status || errno);
}

static int	add_map_line(char *str, t_vector *map)
{
	t_vector	line;

	if (ft_vector_init(&line, (t_vinfos){sizeof(char), 0, NULL}))
		return (1);
	if (ft_vector_join(&line, str, ft_strlen(str))
		|| ft_vector_add(map, &line))
	{
		ft_vector_free(&line);
		return (1);
	}
	return (0);
}

static int	is_line_valid(char *str)
{
	static char	spawn = '\0';
	char		c;

	c = *str++;
	while (c)
	{
		if (!ft_ischarset(c, MAP_CHARSET))
		{
			ft_dprintf(STDERR_FILENO, MAP_ERR, c, INVAL_CHAR);
			return (0);
		}
		if (ft_ischarset(c, SPAWN_CHARSET))
		{
			if (spawn)
			{
				ft_dprintf(STDERR_FILENO, MAP_ERR2, MULTIPLE_SPAWN);
				return (0);
			}
			else
				spawn = c;
		}
		c = *str++;
	}
	return (1);
}
