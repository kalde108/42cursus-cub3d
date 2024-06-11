/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_enclosed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:41:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:41:49 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft.h"
#include "parsing.h"

static int	is_enclosed(t_vector *map, t_v2d_i start, t_cubscene *scene);
static int	flood_fill_routine(t_vector *map, t_vector *buf, t_cubscene *scene);
static int	init_portal(char *cell, t_v2d_i position, t_cubscene *scene);

int	is_player_enclosed(t_vector *map, t_c3_env *env)
{
	int	enclosed;

	enclosed = is_enclosed(map,
			(t_v2d_i){env->player.camera.pos.x, env->player.camera.pos.y},
			&env->scene);
	if (INVAL_FATAL == enclosed)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (0);
	}
	if (VALID_MAP != enclosed)
		return (0);
	return (1);
}

static int	is_enclosed(t_vector *map, t_v2d_i start, t_cubscene *scene)
{
	t_vector	buf;
	int			enclosed;

	if (ft_vector_init(&buf, sizeof(t_v2d_i), 0, NULL)
		|| ft_vector_add(&buf, &start))
	{
		ft_vector_free(&buf);
		return (-1);
	}
	enclosed = VALID_MAP;
	while (buf.total > 0 && enclosed == VALID_MAP)
		enclosed = flood_fill_routine(map, &buf, scene);
	ft_vector_free(&buf);
	return (enclosed);
}

static int	flood_fill_routine(t_vector *map, t_vector *buf, t_cubscene *scene)
{
	t_v2d_i		current;
	char		*cell;

	current = *(t_v2d_i *)ft_vector_get(buf, buf->total - 1);
	ft_vector_delete(buf, buf->total - 1);
	cell = ft_vector_get(ft_vector_get(map, current.y), current.x);
	if (NULL == cell)
	{
		ft_dprintf(STDERR_FILENO, INVAL_PORTAL_CELL, current.x, current.y);
		return (INVAL_WALL);
	}
	if (ft_ischarset(*cell, ".abcdefghijklmnopqrstuvwxyz"))
		return (VALID_MAP);
	if (*cell == 'P' || *cell == - 'P')
		return (init_portal(cell, current, scene));
	*cell = '.';
	if (ft_vector_add(buf, &(t_v2d_i){current.x, current.y - 1})
		|| ft_vector_add(buf, &(t_v2d_i){current.x - 1, current.y})
		|| ft_vector_add(buf, &(t_v2d_i){current.x, current.y + 1})
		|| ft_vector_add(buf, &(t_v2d_i){current.x + 1, current.y}))
		return (INVAL_FATAL);
	return (VALID_MAP);
}

static int	init_portal(char *cell, t_v2d_i current, t_cubscene *scene)
{
	t_portal	portal;

	if ('P' == *cell)
	{
		*cell = - 'P';
		if (scene->portals.total == MAX_PORTALS)
		{
			ft_dprintf(STDERR_FILENO, MAP_ERR2, TOO_MANY_PORTALS);
			return (INVAL_PORTAL);
		}
		portal.id = scene->portals.total;
		portal.pos = current;
		portal.face = -1;
		portal.is_open = false;
		portal.linked_portal = NO_LINK;
		*(scene->portals.tab + scene->portals.total) = portal;
		scene->portals.total++;
		return (VALID_MAP);
	}
	ft_dprintf(STDERR_FILENO, INVAL_PORTAL_CELL, current.x, current.y);
	return (INVAL_PORTAL);
}
