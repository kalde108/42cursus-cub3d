/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:58:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 05:50:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "libft.h"
#include "cub3ddef.h"
#include "parsing.h"

# include <stdio.h>

static int			get_textures_and_colors(int fd, t_cubscene *ptr);
static int			tokenize_line(char *line, t_cubscene *ptr);
static t_identifier	get_identifier(char *str);
static int			is_defined(char *tok, t_identifier id, t_cubscene scene);

int	get_cubscene(char *path, t_cubscene *ptr)
{
	int			status;
	// t_cubscene	scene;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, path, strerror(errno));
		return (1);
	}
	status = get_textures_and_colors(fd, ptr);
	if (!status)
		status = 0;
	close(fd);
	return (status);
}

static	int	get_textures_and_colors(int fd, t_cubscene *ptr)
{
	int		status;
	char	*gnl;
	int		id;

	status = 0;
	id = 0;
	while (!status && !get_next_line(fd, &gnl) && gnl && id < 6)
	{
		if (gnl[0] != '\n')
		{
			status = tokenize_line(gnl, ptr);
			id++;
		}
		free(gnl);
	}
	return (status);
}


static int	tokenize_line(char *line, t_cubscene *ptr)
{
	char			*tok;
	char			*value;
	t_identifier	id;

	tok = ft_strtok(line, " \n");
	if (tok)
		id = get_identifier(tok);
	if (!tok || id == ID_INVAL || is_defined(tok, id, *ptr))
		return (1);
	value = ft_strtok(NULL, " \n");
	if (value && set_scene_info(tok, value, id, ptr))
		return (1);
	if (!ft_strtok(NULL, " \n"))
		return (0);
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, tok, INVAL_DEF);
	return (1);
}

static t_identifier	get_identifier(char *str)
{
	const char		*indentifier[] = {
		NORTH,
		SOUTH,
		EAST,
		WEST,
		FLOOR,
		CEILING,
		NULL
	};
	t_identifier	i;

	i = ID_NORTH;
	while (indentifier[i])
	{
		if (!ft_strcmp(indentifier[i], str))
			return (i);
		i++;
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, str, INVAL_ID);
	return (ID_INVAL);
}

static int	is_defined(char *tok, t_identifier id, t_cubscene scene)
{
	if (id == ID_FLOOR
		&& scene.floor.r | scene.floor.g | scene.floor.b == COLOR_INIT)
		return (0);
	else if (id == ID_CEILING
		&& scene.ceilling.r | scene.ceilling.g | scene.ceilling.b == COLOR_INIT)
		return (0);
	else if ((id == ID_NORTH && !scene.texture.north)
		|| (id == ID_SOUTH && !scene.texture.south)
		|| (id == ID_EAST && !scene.texture.east)
		|| (id == ID_WEST && !scene.texture.west))
		return (0);
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, tok, MULTI_ID);
	return (1);
}
