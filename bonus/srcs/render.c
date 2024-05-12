/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/11 20:09:42 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "mlx.h"
#include "render.h"
#include "draw.h"

# include <stdio.h>
# include <unistd.h>

int	render(t_c3_env *env)
{
	size_t	time;
	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	// while (env->frame_time < FRAME_TIME)
	// {
	// 	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	// 	usleep(1000);
	// }
	start_timer(&env->frame_timer);
	dprintf(2, "fps: %f\n", 1 / env->frame_time);
	update_player(env);
	time = get_time();
	if (draw_backgound(env))
		mlx_loop_end(env->mlx);
	// draw_backgound(env);
	dprintf(2, "floor_and_ceiling: %zums\n", get_time() - time);
	time = get_time();
	if (render_map(env))
		mlx_loop_end(env->mlx);
	dprintf(2, "render_map: %zums\n", get_time() - time);
	// draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
