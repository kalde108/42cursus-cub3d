/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:49:06 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:49:07 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

void	minimap(t_c3_env *env)
{
	double	angle;

	angle = player_angle(env->player.camera.dir);
	mini_scene(env, angle);
	if (env->options.minimap.view)
		mini_view_cone(env);
	mini_player(&env->img, angle, &env->options.minimap);
}
