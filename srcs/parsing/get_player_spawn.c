/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:15:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 19:59:07 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "cub3d.h"

static void	get_player_orientation(char c, t_player *player);

int	get_player_spawn(char **map, t_player *player)
{
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_ischarset(map[y][x], SPAWN_CHARSET))
			{
				player->pos.x = y;
				player->pos.y = x;
				get_player_orientation(map[y][x], player);
				map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	//ERROR MESSAGE, NO PLAYER FOUND
	return (1);
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
	player->plane.x = player->dir.y * 0.66;
	player->plane.y = -player->dir.x * 0.66;
}
