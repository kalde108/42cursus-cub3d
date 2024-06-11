/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_minimap_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:50:49 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:50:52 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	op_minimap_size(t_c3_env *env)
{
	if (env->key_state[KEY_CTRL_L])
	{
		if (env->key_state[KEY_KP_ADD])
		{
			if (env->options.minimap.size < HEIGHT)
				env->options.minimap.size *= 1.01;
		}
		if (env->key_state[KEY_KP_SUB])
		{
			if (env->options.minimap.size > 100.0)
				env->options.minimap.size *= 0.99;
		}
	}
	if (env->options.minimap.pos.x < env->options.minimap.size >> 1)
		env->options.minimap.pos.x = env->options.minimap.size >> 1;
	if (env->options.minimap.pos.x >= WIDTH - (env->options.minimap.size >> 1))
		env->options.minimap.pos.x = WIDTH - (env->options.minimap.size >> 1);
	if (env->options.minimap.pos.y < env->options.minimap.size >> 1)
		env->options.minimap.pos.y = env->options.minimap.size >> 1;
	if (env->options.minimap.pos.y >= HEIGHT - (env->options.minimap.size >> 1))
		env->options.minimap.pos.y = HEIGHT - (env->options.minimap.size >> 1);
}
