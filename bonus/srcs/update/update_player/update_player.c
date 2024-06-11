/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:57:04 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:57:06 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

void	update_player(t_c3_env *env)
{
	env->player.mv_speed = PLAYER_MOVEMENT_SPEED * env->frame_time / 1000.0;
	env->player.rt_speed = PLAYER_ROTATION_SPEED * env->frame_time / 1000.0;
	player_mouvement(&env->scene, &env->player, env->key_state);
	player_rotation(&env->player, &env->mouse, env->key_state);
}
