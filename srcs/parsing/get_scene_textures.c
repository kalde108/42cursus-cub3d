/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:03:05 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 20:40:40 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing.h"

static int			tokenize_line(char *line, t_cubscene *ptr, int *defined);
static t_identifier	get_identifier(char *str);
static int			is_defined(char *tok, int *control);

int	get_scene_textures(int fd, t_cubscene *ptr)
{
	int		defined[IDENTIFIERS];
	int		parsed;
	int		status;
	char	*gnl;

	ft_memset(defined, 0, sizeof(int) * IDENTIFIERS);
	status = 0;
	parsed = 0;
	while (parsed < IDENTIFIERS && !status && !get_next_line(fd, &gnl) && gnl)
	{
		ft_replace_char(gnl, '\n', '\0');
		if ('\0' != *gnl)
		{
			status = tokenize_line(gnl, ptr, defined);
			parsed++;
		}
		free(gnl);
	}
	return (status);
}

#include <stdio.h>

static int	tokenize_line(char *line, t_cubscene *ptr, int *defined)
{
	char			*identifier;
	char			*value;
	t_identifier	id;

	identifier = ft_strtok(line, " ");
	if (identifier)
		id = get_identifier(identifier);
	// printf("------tok=%s\n", identifier);
	if (!identifier || id == ID_INVAL || is_defined(identifier, defined + id))
		return (1);
	value = ft_strtok(NULL, "");
	// printf("------value=%s\n", value);
	if (value && set_texture(identifier, value, id, ptr))
		return (1);
	return (0);
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

static int	is_defined(char *tok, int *control)
{
	if (0 == *control)
	{
		*control = 1;
		return (0);
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, tok, MULTI_ID);
	return (1);
}
