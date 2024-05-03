/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:26:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 21:46:32 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "cubscene.h"
#include "parsing.h"

static int	set_texture_color(char *idtok, char *str, t_cubscene_color *texture);
static int	get_color_channel(char *tok, unsigned char *channel, char *idtok);

int	set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr)
{
	char	*dup;

	if (id == ID_FLOOR)
		return (set_texture_color(tok, str, &ptr->floor));
	else if (id == ID_CEILING)
		return (set_texture_color(tok, str, &ptr->ceilling));
	dup = ft_strdup(str);
	if (!dup)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
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

static int	set_texture_color(char *idtok, char *str, t_cubscene_color *texture)
{
	char	*tok;

	errno = 0;
	tok = ft_strtok(str, ",");
	if (tok && get_color_channel(tok, &texture->r, idtok))
		return (1);
	tok = ft_strtok(NULL, ",");
	if (tok && get_color_channel(tok, &texture->g, idtok))
		return (1);
	tok = ft_strtok(NULL, ",");
	if (tok && get_color_channel(tok, &texture->b, idtok))
		return (1);
	if (ft_strtok(NULL, " ,\n"))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_COLOR); //CHECK ERROR MSG
		return (1);
	}
	texture->a = 0;
	return (0);
}

# include <stdio.h>

static int	get_color_channel(char *tok, unsigned char *channel, char *idtok)
{
	long	value;

	if (!ft_isdigit(tok[0]))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_COLOR);
		return (1);
	}
	value = ft_strtol(tok, NULL);
	if (!errno && value >= 0 && value <= 255)
	{
		*channel = value;
		return (0);
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_RANGE);
	return (1);
}
