/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:57:04 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/19 18:21:40 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

void	update_player(t_c3_env *env)
{
	if (env->key_state[KEY_SHIFT_L])
		env->player.mv_speed = PLAYER_RUNNING_SPEED * env->frame_time / 1000.0;
	else
		env->player.mv_speed = PLAYER_WALKING_SPEED * env->frame_time / 1000.0;
	env->player.rt_speed = PLAYER_ROTATION_SPEED * env->frame_time / 1000.0;
	player_mouvement(&env->scene, &env->player, env->key_state);
	player_rotation(&env->player, &env->mouse, env->key_state);
}
