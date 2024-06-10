/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focusout_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:05:53 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 20:06:12 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "cub3d.h"

int	focusout_hook(t_c3_env *env)
{
	int	i;

	i = 0;
	while (i < KEY_COUNT)
	{
		env->key_state[i] = 0;
		i++;
	}
	env->mouse.status = false;
	mlx_mouse_show(env->mlx, env->win);
	return (0);
}
