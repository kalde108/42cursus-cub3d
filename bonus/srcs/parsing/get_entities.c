/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:13:57 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 19:03:43 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cubscene.h"
#include "parsing.h"
#include "cub3d.h"

int	get_entities(t_vector *map, t_c3_env *env)
{
	if (get_player_spawn(map, &env->player))
		return (-1);
	if (get_monster_spawn(map, &env->monster))
		return (-1);
	// if (1 != is_player_enclosed(map, env))
	// 	return (-1);
	return (0);
}
