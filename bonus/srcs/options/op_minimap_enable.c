/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_minimap_enable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:50:36 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:50:37 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	op_minimap_enable(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_M])
	{
		if (true == key_release)
		{
			env->options.minimap.enable = !env->options.minimap.enable;
		}
		key_release = false;
	}
	else
		key_release = true;
}
