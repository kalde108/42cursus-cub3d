/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:15:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 18:59:12 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "cub3d.h"

static void	get_player_orientation(char c, t_v2d_d *dir);

int	get_player_spawn(char **map, t_v2d_d *pos, t_v2d_d *dir)
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
				pos->x = y;
				pos->y = x;
				get_player_orientation(map[y][x], dir);
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

static void	get_player_orientation(char c, t_v2d_d *dir)
{
	const char		charset[] = {'N', 'S', 'E', 'W'};
	const double	x[] = {0, 0, 1, -1};
	const double	y[] = {-1, 1, 0, 0};
	int				i;

	i = 0;
	while (charset[i] != c)
		i++;
	dir->x = x[i];
	dir->y = y[i];
}
