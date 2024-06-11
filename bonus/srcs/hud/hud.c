/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:12:31 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 20:12:33 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	hud(t_c3_env *env)
{
	crosshair(env);
	interaction_cooldown(env);
	if (env->options.minimap.enable)
		minimap(env);
}
