/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_enclosed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:04:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 13:48:48 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "cub3d.h"
#include "libft.h"
#include "parsing.h"

# include <stdio.h> //REMOVE

void 		DEBUG_PRINT_MAP(t_cubscene scene); //REMOVE

static int	is_enclosed(t_cubscene *scene, int x, int y);
static int	flood_fill_routine(t_cubscene *scene, t_vector *stack);

int	is_player_enclosed(t_cubscene *scene, t_player *player)
{
	const size_t	mapsize = sizeof(char) * scene->width * scene->height;
	t_cubscene		dup;
	int				enclosed;

	dup.map = malloc(mapsize);
	if (!dup.map)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (0);
	}
	ft_memcpy(dup.map, scene->map, mapsize);
	dup.width = scene->width;
	dup.height = scene->height;
	enclosed = is_enclosed(&dup, player->pos.x, player->pos.y);
	if (!enclosed)
		ft_dprintf(STDERR_FILENO, MAP_ERR2, NON_ENCLOSED);
	else if (enclosed == -1)
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
	free(dup.map);
	return (enclosed == 1);
}

static int	is_enclosed(t_cubscene *scene, int x, int y)
{
	t_vector	stack;
	int			enclosed;

	stack = (t_vector){0};
	stack.infos.data_size = sizeof(t_v2d_i);
	stack.infos.capacity = 0;
	stack.infos.del = NULL;
	if (ft_vector_init(&stack, stack.infos)
		|| ft_vector_add(&stack, &(t_v2d_i){x, y}))
	{
		ft_vector_free(&stack);
		return (-1);
	}
	enclosed = 1;
	while (stack.total > 0 && enclosed == 1)
		enclosed = flood_fill_routine(scene, &stack);
	ft_vector_free(&stack);
	return (enclosed);
}

static int	flood_fill_routine(t_cubscene *scene, t_vector *stack)
{
	char		*c;
	t_v2d_i		pos;

	pos = *(t_v2d_i *)ft_vector_get(stack, stack->total - 1);
	ft_vector_delete(stack, stack->total - 1);
	if (pos.x < 0 || pos.x >= scene->width
		|| pos.y < 0 || pos.y >= scene->height)
		return (0);
	c = scene->map + (pos.y * scene->width) + pos.x;
	if (!ft_ischarset(*c, ENCLOSURE_CHARSET))
	{
		*c = '1';
		if (ft_vector_add(stack, &(t_v2d_i){pos.x, pos.y - 1})
			|| ft_vector_add(stack, &(t_v2d_i){pos.x - 1, pos.y})
			|| ft_vector_add(stack, &(t_v2d_i){pos.x, pos.y + 1})
			|| ft_vector_add(stack, &(t_v2d_i){pos.x + 1, pos.y}))
			return (-1);
	}
	return (1);
}
