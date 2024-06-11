/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_minimap_zoom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:25 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:51:26 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	op_minimap_zoom(t_c3_env *env)
{
	if (!env->key_state[KEY_CTRL_L])
	{
		if (env->key_state[KEY_KP_ADD])
		{
			if (env->options.minimap.zoom < 50.0)
				env->options.minimap.zoom *= 1.01;
		}
		if (env->key_state[KEY_KP_SUB])
		{
			if (env->options.minimap.zoom > 1.0)
				env->options.minimap.zoom *= 0.99;
		}
	}
}
