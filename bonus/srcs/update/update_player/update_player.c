/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/07 17:42:32 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "key_index.h"
#include "libft.h"
#include "tile_address.h"

#include <math.h>

# include <stdio.h>

static void	update_rotation(t_c3_env *env)
{
	if (env->key_state[KEY_RIGHT])
		rotate_player(&env->player, env->player.rt_speed);
	if (env->key_state[KEY_LEFT])
		rotate_player(&env->player, -env->player.rt_speed);
	if (env->mouse.delta.x)
	{
		rotate_player(&env->player, MOUSE_SENSIVITY * (double)env->mouse.delta.x * env->player.rt_speed);
		env->mouse.delta.x = 0;
	}
}

void	update_player(t_c3_env *env)
{
	env->player.mv_speed = PLAYER_MOVEMENT_SPEED * env->frame_time;
	env->player.rt_speed = PLAYER_ROTATION_SPEED * env->frame_time;
	update_pos(env);
	update_rotation(env);
}
