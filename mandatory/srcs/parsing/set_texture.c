/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:26:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 20:50:26 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"

static int	set_texture_filepath(char *filepath, t_tex *ptr);
static int	set_texture_color(char *idtok, char *str, __uint32_t *texture);
static int	get_color_channel(char *tok,
				__uint32_t *color,
				int channel,
				char *idtok);

int	set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr)
{
	if (id == ID_FLOOR)
		return (set_texture_color(tok, str, &ptr->floor));
	else if (id == ID_CEILING)
		return (set_texture_color(tok, str, &ptr->ceiling));
	if (set_texture_filepath(str, ptr->texture + id))
		return (1);
	return (0);
}

static int	set_texture_filepath(char *filepath, t_tex *ptr)
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

static int	set_texture_color(char *idtok, char *str, __uint32_t *color)
{
	char	*tok;

	errno = 0;
	tok = ft_strtok(str, ",");
	if (tok && get_color_channel(tok, color, 16, idtok))
		return (1);
	tok = ft_strtok(NULL, ",");
	if (tok && get_color_channel(tok, color, 8, idtok))
		return (1);
	tok = ft_strtok(NULL, ",");
	if (tok && get_color_channel(tok, color, 0, idtok))
		return (1);
	tok = ft_strtok(NULL, "");
	if (tok != NULL)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_COLOR);
		return (1);
	}
	return (0);
}

static int	get_color_channel(char *tok,
				__uint32_t *color,
				int channel,
				char *idtok)
{
	long	value;
	size_t	i;

	i = 0;
	if (tok[i] == '-')
		i++;
	while (tok[i])
	{
		if (!ft_isdigit(tok[i]))
		{
			ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_COLOR);
			return (1);
		}
		i++;
	}
	value = ft_strtol(tok, NULL);
	if (!errno && value >= 0 && value <= 255)
	{
		*color |= (value << channel);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR2, idtok, INVAL_RANGE);
	return (1);
}
