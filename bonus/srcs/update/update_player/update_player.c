/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/29 18:44:18 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "key_index.h"
#include "libft.h"
#include "tile_address.h"

#include <math.h>

# include <stdio.h>

static void	apply_rotation(t_c3_env *env, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = env->player.dir.x;
	env->player.dir.x = env->player.dir.x * cos(angle) \
						- env->player.dir.y * sin(angle);
	env->player.dir.y = old_dir_x * sin(angle) + env->player.dir.y * cos(angle);
	old_plane_x = env->player.plane.x;
	env->player.plane.x = env->player.plane.x * cos(angle) \
							- env->player.plane.y * sin(angle);
	env->player.plane.y = old_plane_x * sin(angle) + \
							env->player.plane.y * cos(angle);
}

static void	update_rotation(t_c3_env *env)
{
	if (env->key_state[KEY_RIGHT])
		apply_rotation(env, env->player.rt_speed);
	if (env->key_state[KEY_LEFT])
		apply_rotation(env, -env->player.rt_speed);
	if (env->mouse.delta)
	{
		apply_rotation(env, MOUSE_SENSIVITY * (double)env->mouse.delta * env->player.rt_speed);
		env->mouse.delta = 0;
	}
}

void	update_player(t_c3_env *env)
{
	env->player.mv_speed = PLAYER_MOVEMENT_SPEED * env->frame_time;
	env->player.rt_speed = PLAYER_ROTATION_SPEED * env->frame_time;
	update_pos(env);
	update_rotation(env);
}
