/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:16 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:56:16 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "update.h"
#include "key_index.h"

static t_v2d_d	get_move_dir(int *key_state, t_v2d_d player_dir)
{
	t_v2d_d	move_dir;

	move_dir = (t_v2d_d){0, 0};
	move_dir.x = (key_state[KEY_W] - key_state[KEY_S]) * player_dir.x + \
		(key_state[KEY_A] - key_state[KEY_D]) * player_dir.y;
	move_dir.y = (key_state[KEY_W] - key_state[KEY_S]) * player_dir.y - \
		(key_state[KEY_A] - key_state[KEY_D]) * player_dir.x;
	if ((key_state[KEY_W] || key_state[KEY_S])
		&& (key_state[KEY_A] || key_state[KEY_D]))
	{
		move_dir.x *= SQRT2_2;
		move_dir.y *= SQRT2_2;
	}
	return (move_dir);
}

static t_v2d_d	get_move_vec(int *key_state, t_player *player)
{
	t_v2d_d	move_dir;
	t_v2d_d	move_vec;

	move_dir = get_move_dir(key_state, player->camera.dir);
	move_vec.x = move_dir.x * player->mv_speed;
	move_vec.y = move_dir.y * player->mv_speed;
	return (move_vec);
}

void	player_mouvement(t_cubscene *scene, t_player *player, int *key_state)
{
	t_v2d_d	move_vec;

	move_vec = get_move_vec(key_state, player);
	if (move_vec.x != 0)
		x_mouvement(scene, player, (t_v2d_d){move_vec.x, 0}, &move_vec);
	if (move_vec.y != 0)
		y_mouvement(scene, player, (t_v2d_d){0, move_vec.y});
}
