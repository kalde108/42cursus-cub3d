/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_monster_spawn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:09:46 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/12 16:29:25 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing.h"
#include "cubdef.h"

static int	search_line(t_vector *line, t_entity *monster, bool *found, int y);
static void	init_monster(t_entity *monster);

int	get_monster_spawn(t_vector *map, t_entity *monster)
{
	bool		found;
	t_vector	*line;
	size_t		i;

	found = false;
	i = 0;
	while (i < map->total)
	{
		line = ft_vector_get(map, i++);
		if (search_line(line, monster, &found, i))
			return (-1);
	}
	if (false == found)
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, NO_MONSTER);
		return (-1);
	}
	return (0);
}

static int	search_line(t_vector *line, t_entity *monster, bool *found, int y)
{
	char	*cell;
	size_t	i;

	i = 0;
	while (i < line->total)
	{
		cell = ft_vector_get(line, i++);
		if (MONSTER_CHAR == *cell)
		{
			if (true == *found)
			{
				ft_dprintf(STDERR_FILENO, MAP_ERR2, MULTIPLE_MONSTER);
				return (-1);
			}
			*found = true;
			monster->pos.x = i + 0.5;
			monster->pos.y = y + 0.5;
			init_monster(monster);
			*cell = '.';
		}
	}
	return (0);
}

static void	init_monster(t_entity *monster)
{
	const double	x[] = {0, 0, 1, -1};
	const double	y[] = {-1, 1, 0, 0};
	int				i;

	i = rand() % 4;
	monster->dir.x = x[i];
	monster->dir.y = y[i];
	monster->plane.x = -y[i] * 1.0;
	monster->plane.y = x[i] * 1.0;
	monster->mv_speed = MONSTER_MOVEMENT_SPEED;
	monster->rt_speed = MONSTER_ROTATION_SPEED;
}
