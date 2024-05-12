/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:26:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/12 14:46:17 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "libft.h"
#include "parsing.h"

static int		get_path_type(char *tok, char *path);
static int		set_texture_filepath(char *filepath, t_tex *ptr);
static t_tex	*get_texture_ptr(t_identifier id, t_tex **textures);

int	set_texture(char *tok, char *path, t_identifier id, t_cubscene *scene)
{
	const int	type = get_path_type(tok, path);

	if (SPRITE_FILE == type)
		return (set_texture_filepath(path, get_texture_ptr(id, scene->texture)));
	// else if (SPRITE_DIRECTORY == type)
	// {
	// 	;
	// }
	else
		return (1);
	return (0);
}

static int	get_path_type(char *tok, char *path)
{
	struct stat	buf;

	if (-1 == access(path, F_OK))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR3, tok, path, strerror(errno));
		return (-1);
	}
	if (-1 == stat(path, &buf))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (-1);
	}
	if (0 != S_ISREG(buf.st_mode))
		return (SPRITE_FILE);
	else if (0 != S_ISDIR(buf.st_mode))
		return (SPRITE_DIRECTORY);
	else
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR3, tok, path, INVAL_PATH);
		return (-1);
	}
}

static int	set_texture_filepath(char *filepath, t_tex *texture)
{
	t_texdata	*ptr;

	ptr = ft_calloc(1, sizeof(t_texdata));
	if (NULL == ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	ptr->filepath = ft_strdup(filepath);
	if (NULL == ptr->filepath)
	{
		free(ptr);
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	texture->sprite = ptr;
	texture->n = 1;
	return (0);
}

static t_tex	*get_texture_ptr(t_identifier id, t_tex **textures)
{
	if (id <= ID_CZ)
		return (textures[id / 26] + (id % 26));
	// else
	// 	;
	return (0);
}
