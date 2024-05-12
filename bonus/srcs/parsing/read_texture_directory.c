/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture_directory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:12:35 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/12 18:06:16 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "libft.h"
#include "cubscene.h"
#include "cubdef.h"

static int	read_entries(DIR *dir, t_vector *frames, char *dirpath);
static int	add_frame(t_vector *frames, char *dirpath, char *name);
static int	set_frames(t_tex *texture, t_vector *frames);
static void	free_frame(void *ptr);

int	get_directory_textures(char *dirpath, t_tex *texture)
{
	DIR			*dir;
	int			status;
	t_vector	frames;

	dir = opendir(dirpath);
	if (NULL == dir)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	status = ft_vector_init(&frames, sizeof(t_texdata), 0, free_frame);
	if (0 == status)
		status = read_entries(dir, &frames, dirpath);
	if (0 == status)
		status = set_frames(texture, &frames);
	if (0 != status)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		ft_vector_free(&frames);
	}
	closedir(dir);
	return (status);
}

static int	read_entries(DIR *dir, t_vector *frames, char *dirpath)
{
	struct dirent	*entry;
	int				status;

	errno = 0;
	status = 0;
	entry = readdir(dir);
	while (NULL != entry)
	{
		if ('.' != *entry->d_name)
			status = add_frame(frames, dirpath, entry->d_name);
		entry = readdir(dir);
	}
	return (0 != status || 0 != errno);
}

static int	add_frame(t_vector *frames, char *dirpath, char *name)
{
	t_texdata	tmp;

	tmp = (t_texdata){0};
	tmp.filepath = ft_sprintf("%s%s", dirpath, name);
	if (NULL == tmp.filepath)
		return (1);
	if (SUCCESS != ft_vector_add(frames, &tmp))
	{
		free(tmp.filepath);
		return (1);
	}
	return (0);
}

static int	set_frames(t_tex *texture, t_vector *frames)
{
	if (ft_vector_trim(frames))
		return (1);
	texture->frames = frames->ptr;
	texture->n = frames->total;
	return (0);
}

static void	free_frame(void *ptr)
{
	free(((t_texdata *)ptr)->filepath);
}
