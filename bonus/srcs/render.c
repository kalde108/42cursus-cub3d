/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/11 19:28:12 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "mlx.h"
#include "render.h"
#include "draw.h"

# include <stdio.h>
# include <unistd.h>

int	render(t_c3_env *env)
{
	// dprintf(2, "loop start\n");
	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	// while (env->frame_time < FRAME_TIME)
	// {
	// 	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	// 	usleep(1000);
	// }
	start_timer(&env->frame_timer);
	// dprintf(2, "fps: %f\n", 1 / env->frame_time);
	update_player(env);
	floor_and_ceiling(env);
	// dprintf(2, "render map\n");
	render_map(env);
	// dprintf(2, "put image to window\n");
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
