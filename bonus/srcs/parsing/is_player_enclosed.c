/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_enclosed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:04:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/02 16:38:49 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "libft.h"
#include "cubdef.h"
#include "parsing.h"

static enum e_mapstatus	is_enclosed(t_vector *map, t_v2d_i start, t_cubscene *scene);
static enum e_mapstatus	flood_fill_routine(t_vector *map, t_vector *stack, t_cubscene *scene);
static enum e_mapstatus init_portal(char *cell, t_v2d_i position, t_cubscene *scene);

int	is_player_enclosed(t_vector *map, t_c3_env *env)
{
	enum e_mapstatus	enclosed;

	enclosed = is_enclosed(map,
		(t_v2d_i){env->player.camera.pos.x, env->player.camera.pos.y}, &env->scene);
	if (INVAL_FATAL == enclosed)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (0);
	}
	if (VALID_MAP != enclosed)
		return (0);
	if ('.' != *(char *)(ft_vector_get(ft_vector_get(map, env->monster.pos.y), env->monster.pos.x)))
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, MONSTER_NOPATH);
		return (0);
	}
	return (1);
}

static enum e_mapstatus	is_enclosed(t_vector *map, t_v2d_i start, t_cubscene *scene)
{
	t_vector			stack;
	enum e_mapstatus	enclosed;

	if (ft_vector_init(&stack, sizeof(t_v2d_i), 0, NULL)
		|| ft_vector_add(&stack, &start))
	{
		ft_vector_free(&stack);
		return (-1);
	}
	enclosed = VALID_MAP;
	while (stack.total > 0 && enclosed == VALID_MAP)
		enclosed = flood_fill_routine(map, &stack, scene);
	ft_vector_free(&stack);
	return (enclosed);
}

static enum e_mapstatus	flood_fill_routine(t_vector *map, t_vector *stack, t_cubscene *scene)
{	
	t_v2d_i		current;
	char		*cell;

	current = *(t_v2d_i *)ft_vector_get(stack, stack->total - 1);
	ft_vector_delete(stack, stack->total - 1);
	cell = ft_vector_get(ft_vector_get(map, current.y), current.x);
	if (NULL == cell)
	{
		ft_dprintf(STDERR_FILENO, INVAL_PORTAL_CELL, current.x, current.y);
		return (INVAL_WALL);
	}
	if (ft_ischarset(*cell, ".abcdefghijklmnopqrstuvwxyz"))
		return (VALID_MAP);
	if (*cell == 'P' || *cell == -'P')
		return (init_portal(cell, current, scene));
	*cell = '.';
	if (ft_vector_add(stack, &(t_v2d_i){current.x, current.y - 1})
		|| ft_vector_add(stack, &(t_v2d_i){current.x - 1, current.y})
		|| ft_vector_add(stack, &(t_v2d_i){current.x, current.y + 1})
		|| ft_vector_add(stack, &(t_v2d_i){current.x + 1, current.y}))
		return (INVAL_FATAL);
	return (VALID_MAP);
}

static enum e_mapstatus init_portal(char *cell, t_v2d_i current, t_cubscene *scene)
{
	if ('P' == *cell)
	{
		*cell = -'P';
		if (scene->portals.total == MAX_PORTALS)
		{
			ft_dprintf(STDERR_FILENO, MAP_ERR2, TOO_MANY_PORTALS);
			return (INVAL_PORTAL);
		}
		scene->portals.tab[scene->portals.total].id = scene->portals.total;
		scene->portals.tab[scene->portals.total].pos = current;
		scene->portals.tab[scene->portals.total].linked_portal = -1;
		scene->portals.total++;
		return (VALID_MAP);
	}
	ft_dprintf(STDERR_FILENO, INVAL_PORTAL_CELL, current.x, current.y);
	return (INVAL_PORTAL);
}
