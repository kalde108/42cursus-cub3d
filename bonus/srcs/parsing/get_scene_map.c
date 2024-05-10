/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:25:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/10 23:30:07 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing.h"

static int	read_map_file(int fd, t_vector map[LAYERS_COUNT], t_tex **textures);
static int	read_map_layer(int fd, t_vector map[LAYERS_COUNT], char *charset);
static int	add_map_line(char *str, t_vector map[LAYERS_COUNT]);
static int	is_line_valid(char *str, const char *charset);

int	get_scene_map(int fd, t_cubscene *scene)
{
	t_vector	map[LAYERS_COUNT];
	int			status;
	int			i;

	ft_memset(map, '\0', sizeof(t_vector) * LAYERS_COUNT);
	status = 0;
	i = 0;
	while (0 == status && i < LAYERS_COUNT)
	{
		status = ft_vector_init(map + i, sizeof(t_vector), 0, ft_vvector_free);
		i++;
	}
	if (0 == status)
		status = read_map_file(fd, map, scene->texture);
	if (0 == status)
		status = convert_map(map, scene);
	i = 0;
	while (i < LAYERS_COUNT)
	{
		ft_vector_free(map + i);
		i++;
	}
	return (status);
}

static int	read_map_file(int fd, t_vector map[LAYERS_COUNT], t_tex **textures)
{
	char	*charset;
	int		status;
	int		i;

	status = 0;
	i = 0;
	charset = get_map_charset(textures[i]);
	if (NULL == charset)
		return (-1);
	while (0 == status && i < LAYERS_COUNT)
	{
		status = read_map_layer(fd, map + i, charset);
		free(charset);
		if (0 == status && ++i < LAYERS_COUNT)
		{
			charset = get_layer_charset(textures[i]);
			if (NULL == charset)
				return (-1);
		}
	}
	return (status);
}

static int	read_map_layer(int fd, t_vector map[LAYERS_COUNT], char *charset)
{
	char		*gnl;
	int			status;

	errno = 0;
	status = 0;
	while (0 == status && 0 == get_next_line(fd, &gnl) && NULL != gnl)
	{
		ft_replace_char(gnl, '\n', '\0');
		if ('\0' == *gnl)
		{
			free(gnl);
			return (0);
		}
		ft_dprintf(2, "%s\n", gnl);
		if (is_line_valid(gnl, charset))
			status = add_map_line(gnl, map);
		else
			status = -1;
		free(gnl);
	}
	return (status);
}

static int	add_map_line(char *str, t_vector map[LAYERS_COUNT])
{
	t_vector	line;

	if (ft_vector_init(&line, sizeof(char), 0, NULL))
		return (-1);
	if (ft_vector_join(&line, str, ft_strlen(str))
		|| ft_vector_add(map, &line))
	{
		ft_vector_free(&line);
		return (-1);
	}
	return (0);
}

static int	is_line_valid(char *str, const char *charset)
{
	char		c;

	c = *str++;
	while (c)
	{
		if (!ft_ischarset(c, charset))
		{
			ft_dprintf(STDERR_FILENO, MAP_ERR, c, INVAL_CHAR);
			return (0);
		}
		c = *str++;
	}
	return (-1);
}
