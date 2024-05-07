/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:58:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/06 01:16:44 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"

int	get_cubscene(char *path, t_cubscene *scene)
{
	int			status;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, path, strerror(errno));
		return (-1);
	}
	scene->floor = (uint32_t)255 << 24;
	scene->ceiling = (uint32_t)255 << 24;
	status = get_scene_textures(fd, scene);
	if (!status)
		status = get_scene_map(fd, scene);
	close(fd);
	return (status);
}






