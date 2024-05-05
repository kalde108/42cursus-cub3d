/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_enclosed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:04:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 23:30:04 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "cub3d.h"
#include "libft.h"
#include "parsing.h"

void 		DEBUG_PRINT_MAP(t_cubscene scene); //REMOVE

static int	is_enclosed(t_cubscene *scene, int x, int y);

int	is_player_enclosed(t_cubscene *scene, t_player *player)
{
	const size_t	mapsize = sizeof(char) * scene->width * scene->height;
	t_cubscene		dup;

	dup.map = malloc(mapsize);
	if (!dup.map)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (0);
	}
	ft_memcpy(dup.map, scene->map, mapsize);
	dup.width = scene->width;
	dup.height = scene->height;
	if (is_enclosed(&dup, player->pos.x, player->pos.y))
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, NON_ENCLOSED);
		free(dup.map);
		return (0);
	}
	free(dup.map);
	return (1);
}


static int	is_enclosed(t_cubscene *scene, int x, int y)
{
	char	*c;

	c = scene->map + (y * scene->width) + x;
	if (*c == '1')
		return (0);
	if (x == 0 || x == scene->width - 1
		|| y == 0 || y == scene->height - 1
		|| *c == ' ')
		return (-1);
	*c = '1';
	return (is_enclosed(scene, x, y - 1)
		// || is_enclosed(scene, x + 1, y - 1)
		|| is_enclosed(scene, x + 1, y)
		// || is_enclosed(scene, x + 1, y + 1)
		|| is_enclosed(scene, x, y + 1)
		// || is_enclosed(scene, x - 1, y + 1)
		|| is_enclosed(scene, x - 1, y));
		// || is_enclosed(scene, x - 1, y - 1));
}
