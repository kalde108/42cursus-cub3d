/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:15:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 17:29:10 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

#include "libft.h"
#include "parsing.h"

static int	search_line(t_vector *line, t_entity *player, bool *found, int y);
static void	get_player_orientation(char c, t_entity *player);

int	get_player_spawn(t_vector *map, t_entity *player)
{
	bool		found;
	t_vector	*line;
	size_t		i;

	found = false;
	i = 0;
	while (i < map->total)
	{
		line = ft_vector_get(map, i++);
		if (search_line(line, player, &found, i))
			return (-1);
	}
	if (false == found)
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, NO_PLAYER);
		return (-1);
	}
	return (0);
}

static int	search_line(t_vector *line, t_entity *player, bool *found, int y)
{
	char	*cell;
	size_t	i;

	i = 0;
	while (i < line->total)
	{
		cell = ft_vector_get(line, i++);
		if (1 == ft_ischarset(*cell, SPAWN_CHARSET))
		{
			if (true == *found)
			{
				ft_dprintf(STDERR_FILENO, MAP_ERR2, MULTIPLE_PLAYER);
				return (-1);
			}
			*found = true;
			player->pos.x = i + 0.5;
			player->pos.y = y + 0.5;
			get_player_orientation(*cell, player);
			*cell = '.';
		}
	}
	return (0);
}

static void	get_player_orientation(char c, t_entity *player)
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
	player->plane.x = -y[i] * 1.0;
	player->plane.y = x[i] * 1.0;
	player->mv_speed = PLAYER_MOVEMENT_SPEED;
	player->rt_speed = PLAYER_ROTATION_SPEED;
}
