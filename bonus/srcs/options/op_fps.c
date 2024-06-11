/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:50:33 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:50:33 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	op_fps(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_F])
	{
		if (true == key_release)
			env->options.fps = !env->options.fps;
		key_release = false;
	}
	else
		key_release = true;
}
