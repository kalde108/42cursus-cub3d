/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:20 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:56:20 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

void	player_rotation(t_player *player, t_mouse *mouse, int *key_state)
{
	if (key_state[KEY_RIGHT])
		rotate_player(player, player->rt_speed);
	if (key_state[KEY_LEFT])
		rotate_player(player, -player->rt_speed);
	if (mouse->delta.x)
	{
		rotate_player(player,
			MOUSE_SENSIVITY * mouse->delta.x * player->rt_speed);
		mouse->delta.x = 0;
	}
}
