/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/12 14:03:52 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "mlx.h"
#include "render.h"
#include "draw.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int	render(t_c3_env *env)
{
	size_t	time;
	char	fps_str[9];

	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	// while (env->frame_time < FRAME_TIME)
	// {
	// 	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	// 	usleep(1000);
	// }
	start_timer(&env->frame_timer);
	// dprintf(2, "fps: %f\n", 1 / env->frame_time);
	update_player(env);
	update_entities(env);
	time = get_time();
	if (draw_backgound(env))
		mlx_loop_end(env->mlx);
	// draw_backgound(env);
	// dprintf(2, "floor_and_ceiling: %zums\n", get_time() - time);
	time = get_time();
	if (render_map(env))
		mlx_loop_end(env->mlx);
	// dprintf(2, "render_map: %zums\n", get_time() - time);
	// draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	sprintf(fps_str, "FPS: %3d", (int)(1 / env->frame_time));
	mlx_string_put(env->mlx, env->win, 10, 20, 0x00FFFFFF, fps_str);
	return (0);
}
