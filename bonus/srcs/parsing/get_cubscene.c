/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cubscene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:58:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/12 16:29:18 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"

int	get_cubscene(char *path, t_c3_env *env)
{
	int	status;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, path, strerror(errno));
		return (-1);
	}
	status = get_scene_textures(fd, &env->scene);
	if (0 == status)
		status = get_scene_map(fd, env);
	close(fd);
	return (status);
}
