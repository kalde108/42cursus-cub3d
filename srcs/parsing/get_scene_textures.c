/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:03:05 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 02:10:41 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing.h"

static int			tokenize_line(char *line, t_cubscene *ptr);
static t_identifier	get_identifier(char *str);
static int			is_defined(char *tok, t_identifier id, t_cubscene scene);

int	get_scene_textures(int fd, t_cubscene *ptr)
{
	int		status;
	char	*gnl;
	int		parsed;

	status = 0;
	parsed = 0;
	while (parsed < 6 && !status && !get_next_line(fd, &gnl) && gnl)
	{
		if (gnl[0] != '\n')
		{
			status = tokenize_line(gnl, ptr);
			parsed++;
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
	if (value && set_texture(tok, value, id, ptr))
		return (1);
	if (!ft_strtok(NULL, " \n"))
		return (0);
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, tok, AMBIGUOUS_DEF);
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
	if ((id == ID_FLOOR && scene.floor.a == 255)
		|| (id == ID_CEILING && scene.ceilling.a == 255))
		return (0);
	else if ((id == ID_NORTH && !scene.texture.no.filepath)
		|| (id == ID_SOUTH && !scene.texture.so.filepath)
		|| (id == ID_EAST && !scene.texture.ea.filepath)
		|| (id == ID_WEST && !scene.texture.we.filepath))
		return (0);
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, tok, MULTI_ID);
	return (1);
}
