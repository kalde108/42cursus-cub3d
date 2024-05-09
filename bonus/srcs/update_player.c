/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:40 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 18:01:35 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_index.h"
#include "libft.h"

#include <math.h>

static t_v2d_d	get_move_vec(t_c3_env *env)
{
	t_v2d_d	move_vec;

	move_vec = (t_v2d_d){0, 0};
	if (env->key_state[KEY_W])
	{
		move_vec.x += env->player.dir.x * env->player.mv_speed;
		move_vec.y += env->player.dir.y * env->player.mv_speed;
	}
	if (env->key_state[KEY_S])
	{
		move_vec.x -= env->player.dir.x * env->player.mv_speed;
		move_vec.y -= env->player.dir.y * env->player.mv_speed;
	}
	if (env->key_state[KEY_A])
	{
		move_vec.x += env->player.dir.y * env->player.mv_speed;
		move_vec.y -= env->player.dir.x * env->player.mv_speed;
	}
	if (env->key_state[KEY_D])
	{
		move_vec.x -= env->player.dir.y * env->player.mv_speed;
		move_vec.y += env->player.dir.x * env->player.mv_speed;
	}
	return (move_vec);
}

static void	update_pos(t_c3_env *env)
{
	t_v2d_d	move_vec;
	t_v2d_d	offset;

	move_vec = get_move_vec(env);
	offset.x = ((move_vec.x >= 0) - (move_vec.x < 0)) * PLAYER_SIZE;
	offset.y = ((move_vec.y >= 0) - (move_vec.y < 0)) * PLAYER_SIZE;
	if (ft_ischarset(env->scene.map[(int)env->player.pos.y * env->scene.width + \
	 	(int)(env->player.pos.x + move_vec.x + offset.x)], WALLKABLE_CHARSET))
		env->player.pos.x += move_vec.x;
	// if (env->scene.map[(int)env->player.pos.y * env->scene.width + \
	// 	(int)(env->player.pos.x + move_vec.x + offset.x)] == '0')
	if (ft_ischarset(env->scene.map[(int)(env->player.pos.y + move_vec.y + \
		offset.y) * env->scene.width + (int)env->player.pos.x], WALLKABLE_CHARSET))
		env->player.pos.y += move_vec.y;
	// if (env->scene.map[(int)(env->player.pos.y + move_vec.y + offset.y) * \
	// 	env->scene.width + (int)env->player.pos.x] == '0')
}

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
}

void	update_player(t_c3_env *env)
{
	update_pos(env);
	update_rotation(env);
}
