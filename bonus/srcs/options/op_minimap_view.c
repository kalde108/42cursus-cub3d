/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_minimap_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:00 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:51:01 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	op_minimap_view(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_V])
	{
		if (true == key_release)
			env->options.minimap.view = !env->options.minimap.view;
		key_release = false;
	}
	else
		key_release = true;
}
