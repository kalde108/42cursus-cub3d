/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/16 13:12:08 by kchillon         ###   ########lyon.fr   */
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
	char	debug_str[1000];

	env->frame_time = get_elapsed_time(&env->clocks.frame_timer) / 1000.0;
	start_timer(&env->clocks.frame_timer);
	// dprintf(2, "\nFPS: %f\n", 1 / env->frame_time);
	sprintf(debug_str, "FPS: %f\n", 1 / env->frame_time);
	update_player(env);
	update_entities(env);
	time = get_time();
	update_frames(env);
	// dprintf(2, "frame_updates: %zums\n", get_time() - time);
	sprintf(debug_str, "%sframe_updates: %zums\n", debug_str, get_time() - time);
	time = get_time();
	if (render_backgound(env))
		mlx_loop_end(env->mlx);
	// dprintf(2, "floor_and_ceiling: %zums\n", get_time() - time);
	sprintf(debug_str, "%sfloor_and_ceiling: %zums\n", debug_str, get_time() - time);
	time = get_time();
	if (render_map(env))
		mlx_loop_end(env->mlx);
	// dprintf(2, "render_map: %zums\n", get_time() - time);
	sprintf(debug_str, "%srender_map: %zums\n", debug_str, get_time() - time);
	// draw_minimap(env);
	time = get_time();
	render_entities(env);
	// dprintf(2, "render_entities: %zums\n", get_time() - time);
	sprintf(debug_str, "%srender_entities: %zums\n", debug_str, get_time() - time);
	dprintf(2, "%s\n", debug_str);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	sprintf(fps_str, "FPS: %3d", (int)(1 / env->frame_time));
	mlx_string_put(env->mlx, env->win, 10, 20, 0x00FFFFFF, fps_str);
	return (0);
}
