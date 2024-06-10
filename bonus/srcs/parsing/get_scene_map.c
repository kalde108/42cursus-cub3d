/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:41:40 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:41:42 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing.h"

static int	read_map_file(int fd, t_vector map[LAYER_COUNT], t_elem **textures);
static int	read_map_layer(int fd, t_vector map[LAYER_COUNT], char *charset);
static int	add_map_line(char *str, t_vector map[LAYER_COUNT]);
static int	is_line_valid(char *str, const char *charset);

int	get_scene_map(int fd, t_c3_env *env)
{
	t_vector	map[LAYER_COUNT];
	int			status;
	int			i;

	ft_memset(map, '\0', sizeof(t_vector) * LAYER_COUNT);
	status = 0;
	i = 0;
	while (0 == status && i < LAYER_COUNT)
	{
		status = ft_vector_init(map + i, sizeof(t_vector), 0, ft_vvector_free);
		i++;
	}
	if (0 == status)
		status = read_map_file(fd, map, env->scene.elems);
	if (0 == status)
		status = get_entities(map, env);
	if (0 == status)
		status = convert_map(map, &env->scene);
	i = 0;
	while (i < LAYER_COUNT)
	{
		ft_vector_free(map + i);
		i++;
	}
	return (status);
}

static int	read_map_file(int fd, t_vector map[LAYER_COUNT], t_elem **textures)
{
	char	*charset;
	int		status;
	int		i;

	status = 0;
	i = 0;
	charset = get_map_charset(textures);
	if (NULL == charset)
		return (-1);
	while (0 == status && i < LAYER_COUNT)
	{
		status = read_map_layer(fd, map + i, charset);
		free(charset);
		if (0 == status && ++i < LAYER_COUNT)
		{
			charset = get_layer_charset(textures[i]);
			if (NULL == charset)
				return (-1);
		}
	}
	return (status);
}

static int	read_map_layer(int fd, t_vector map[LAYER_COUNT], char *charset)
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
		if (is_line_valid(gnl, charset))
			status = add_map_line(gnl, map);
		else
			status = -1;
		free(gnl);
	}
	return (status);
}

static int	add_map_line(char *str, t_vector map[LAYER_COUNT])
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
