/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:26:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 05:45:02 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "cubscene.h"
#include "parsing.h"

static int	set_scene_color(char *idtok, char *str, t_cubscene_color *texture);
static int	check_num_range(char *idtok, t_cubscene_color texture);

int	set_scene_info(char *tok, char *str, t_identifier id, t_cubscene *ptr)
{
	char	*dup;

	if (id == ID_FLOOR)
		return (set_scene_color(tok, str, &ptr->floor));
	else if (id == ID_CEILING)
		return (set_scene_color(tok, str, &ptr->ceilling));
	dup = ft_strdup(str);
	if (!dup)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL_SCENE, strerror(errno));
		return (1);
	}
	else if (id == ID_NORTH)
		ptr->texture.north = dup;
	else if (id == ID_SOUTH)
		ptr->texture.south = dup;
	else if (id == ID_WEST)
		ptr->texture.west = dup;
	else
		ptr->texture.east = dup;
	return (0);
}

static int	set_scene_color(char *idtok, char *str, t_cubscene_color *texture)
{
	char	*tok;

	errno = 0;
	tok = ft_strtok(str, ",\n");
	if (tok)
		texture->r = ft_strtol(tok, NULL);
	tok = ft_strtok(NULL, ",\n");
	if (tok)
		texture->g = ft_strtol(tok, NULL);
	tok = ft_strtok(NULL, ",\n");
	if (tok)
		texture->b = ft_strtol(tok, NULL);
	if (ft_strtok(NULL, ","))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_DEF);
		return (1);
	}
	return (check_num_range(idtok, *texture));
}

static int	check_num_range(char *idtok, t_cubscene_color texture)
{

	if (!errno && texture.r >= 0 && texture.r <= 255
		&& texture.g >= 0 && texture.g <= 255
		&& texture.b >= 0 && texture.b <= 255)
		return (0);
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, strerror(EINVAL));
	return (1);
}
