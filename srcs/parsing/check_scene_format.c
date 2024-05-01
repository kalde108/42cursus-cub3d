/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:01:30 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 02:16:09 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parsing.h"

int	check_scene_format(char *path)
{
	int	len;

	if (!path)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR, NO_SCENE);
		return (1);
	}
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".cub"))
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, path, INVAL_FILE);
		return (1);
	}
	return (0);
}
