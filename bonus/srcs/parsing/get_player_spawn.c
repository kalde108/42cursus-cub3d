/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:15:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 14:19:22 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>

#include "cub3d.h"
#include "libft.h"
#include "parsing.h"

# include <stdio.h>

static void	get_player_orientation(char c, t_player *player);

int	get_player_spawn(t_cubscene scene, t_player *player)
{
	const size_t	size = scene.width * scene.height;
	size_t			i;

	player->pos.x = -1;
	i = -1;
	while (++i < size)
	{
		if (ft_ischarset(scene.map[i], SPAWN_CHARSET))
		{
			if (player->pos.x != -1)
			{
				ft_dprintf(STDERR_FILENO, MAP_ERR2, MULTIPLE_SPAWN);
				return (1);
			}
			player->pos.x = i % scene.width + 0.5;
			player->pos.y = i / scene.width + 0.5;
			get_player_orientation(scene.map[i], player);
			scene.map[i] = '0';
		}
	}
	if (player->pos.x == -1)
		ft_dprintf(STDERR_FILENO, MAP_ERR2, NO_SPAWN);
	return (player->pos.x == -1);
}

static void	get_player_orientation(char c, t_player *player)
{
	const char		charset[] = {'N', 'S', 'E', 'W'};
	const double	x[] = {0, 0, 1, -1};
	const double	y[] = {-1, 1, 0, 0};
	int				i;

	i = 0;
	while (charset[i] != c)
		i++;
	player->dir.x = x[i];
	player->dir.y = y[i];
	player->plane.x = -y[i] * tan(FOV / 2.0 * PI / 180.0);
	player->plane.y = x[i] * tan(FOV / 2.0 * PI / 180.0);
	player->mv_speed = PLAYER_MOVEMENT_SPEED;
	player->rt_speed = PLAYER_ROTATION_SPEED;
}
