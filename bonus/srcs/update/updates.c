/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:33 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:42:35 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

void	updates(t_c3_env *env)
{
	if (env->mouse.status == MOUSE_BUTTON_LEFT)
		update_mouse(env);
	update_player(env);
	update_frames(env);
	player_interaction(env);
	cub_options(env);
}
