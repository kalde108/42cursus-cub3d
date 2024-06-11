/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/11 18:16:08 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "tile_address.h"

static int	get_interaction_cell(t_c3_env *env);

void	player_interaction(t_c3_env *env)
{
	static bool	key_release = true;
	int			cell;

	if (env->key_state[KEY_E])
	{
		if (true == key_release && 0 != timer_is_over(&env->player.interact))
		{
			cell = get_interaction_cell(env);
			if (EMPTY_CELL != cell)
			{
				start_timer(&env->player.interact);
				env->player.succesful_interact = \
				update_portal_status(&env->scene.portals,
						(cell & PORTAL_MASK) >> PORTAL_SHIFT);
			}
		}
		key_release = false;
	}
	else
		key_release = true;
}

static int	get_interaction_cell(t_c3_env *env)
{
	t_hit_buffer	hit_buf[MAX_LAYERS];

	single_raycast(&env->scene, env->player.camera, hit_buf);
	if (hit_buf->cell & TYPE_PORTAL && hit_buf->z <= INTERACTION_DISTANCE)
		return (hit_buf->cell);
	return (EMPTY_CELL);
}
