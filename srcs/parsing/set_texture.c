/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:26:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 02:09:37 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "mlx.h"
#include "libft.h"
#include "cubscene.h"
#include "parsing.h"

static int	set_texture_filepath(char *filepath, t_img *ptr);
static int	set_texture_color(char *idtok, char *str, t_cubscene_color *texture);
static int	get_color_channel(char *tok, unsigned char *channel, char *idtok);

int	set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr)
{
	t_img *img;

	if (id == ID_FLOOR)
		return (set_texture_color(tok, str, &ptr->floor));
	else if (id == ID_CEILING)
		return (set_texture_color(tok, str, &ptr->ceilling));
	if (is_xmp_file(str))
		return (1);
	if (id == ID_NORTH)
		img = &ptr->texture.no;
	else if (id == ID_SOUTH)
		img = &ptr->texture.so;
	else if (id == ID_EAST)
		img = &ptr->texture.ea;
	else
		img = &ptr->texture.we;
	if (set_texture_filepath(str, img))
		return (1);
	return (0);
}

static int	set_texture_filepath(char *filepath, t_img *ptr)
{
	char	*dup;

	dup = ft_strdup(filepath);
	if (NULL == dup)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	ptr->filepath = dup;
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
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok,  AMBIGUOUS_DEF);
		return (1);
	}
	texture->a = 0;
	return (0);
}

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
