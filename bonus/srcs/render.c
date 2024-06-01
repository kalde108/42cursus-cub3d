/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/01 18:34:14 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "mlx.h"
#include "render.h"
#include "draw.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

static void	update_mouse(t_c3_env *env)
{
	int	x;

	mlx_mouse_get_pos(env->mlx, env->win, &x, &env->mouse.y);
	env->mouse.delta = x - env->mouse.x;
	if (x < 1)
	{
		mlx_mouse_move(env->mlx, env->win, WIDTH - 2, env->mouse.y);
		env->mouse.x = WIDTH - 2;
	}
	else if (x >= WIDTH - 1)
	{
		mlx_mouse_move(env->mlx, env->win, 1, env->mouse.y);
		env->mouse.x = 1;
	}
	else
		env->mouse.x = x;
	if (env->mouse.y < 1)
	{
		mlx_mouse_move(env->mlx, env->win, env->mouse.x, HEIGHT - 2);
		env->mouse.y = HEIGHT - 2;
	}
	else if (env->mouse.y >= HEIGHT - 1)
	{
		mlx_mouse_move(env->mlx, env->win, env->mouse.x, 1);
		env->mouse.y = 1;
	}
}

static void	render_hud(t_c3_env *env)
{
	// t_img	*img;
	// int		x;
	// int		y;

	// img = &env->img;
	// y = 0;
	// while (y < 30)
	// {
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		*(unsigned int *)(img->addr + ((y << img->line_length) + x * (img->bits_per_pixel / 8))) = 0x00000000;
	// 		x++;
	// 	}
	// 	y++;
	// }
	draw_crosshair(env);
}

// # include "raycasting.h"
// # include "tile_address.h"
// static void	print_wall_dist(t_c3_env *env)
// {
// 	t_ray			ray;
// 	int				x;
// 	int				hit_count;
// 	t_camera		tmp_camera;
// 	t_hit_buffer	hit_buf;

// 	x = 1024;
// 	hit_count = 0;
// 	ray.total_perp_wall_dist = 0;
// 	ray.hit_type = 0;
// 	tmp_camera.pos = env->player.pos;
// 	tmp_camera.dir = env->player.dir;
// 	tmp_camera.plane = env->player.plane;
// 	while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
// 	{
// 		if (IS_PORTAL(ray.hit_type))
// 			portal_hit(&env->scene, &ray, &tmp_camera);
// 		screen_ray_calculation(&tmp_camera, &ray, x);
// 		ft_dda(&env->scene, &ray);
// 		hit_buf.side = ray.side;
// 		hit_buf.cell = ray.hit_type;
// 		hit_buf.z = ray.perp_wall_dist;
// 		dprintf(2, "%d. ray.perp_wall_dist: %f\n", hit_count, ray.perp_wall_dist);
// 		hit_buf.texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
// 		hit_buf.tex_x = get_tex_x(&ray, hit_buf.texture->width, &tmp_camera);
// 		get_line_y(&hit_buf, ray.perp_wall_dist);
// 		hit_buf.camera = tmp_camera;
// 		hit_count++;
// 	}
// }

int	render(t_c3_env *env)
{
	// size_t	time;																		// debug term
	char	fps_str[11];
	// char	debug_str[10000];															// debug term

	// usleep(100000);	// fake load
	env->frame_time = get_elapsed_time(&env->frame_timer) / 1000.0;
	start_timer(&env->frame_timer);
	// sprintf(debug_str, "FPS: %4.2f\n", 1 / env->frame_time);							// debug term

	// print_wall_dist(env);																// debug term

	// updates
	// time = get_time();																	// debug term
	if (env->mouse.status)
		update_mouse(env);
	// sprintf(debug_str, "%supdate_mouse: %3zums\n", debug_str, get_time() - time);		// debug term
	update_player(env);
	update_entities(env);
	// time = get_time();																	// debug term
	update_frames(env);
	// sprintf(debug_str, "%sframe_updates: %3zums\n", debug_str, get_time() - time);		// debug term

	if (raycast(env))
		mlx_loop_end(env->mlx);

	// rendering
	// time = get_time();																	// debug term
	if (render_backgound(env))
		mlx_loop_end(env->mlx);
	// sprintf(debug_str, "%sfloor_and_ceiling: %3zums\n", debug_str, get_time() - time);	// debug term
	// time = get_time();																	// debug term
	if (render_map(env))
		mlx_loop_end(env->mlx);
	// sprintf(debug_str, "%srender_map: %3zums\n", debug_str, get_time() - time);			// debug term
	draw_minimap(env);
	// time = get_time();																	// debug term
	// render_entities(env);
	// sprintf(debug_str, "%srender_entities: %3zums\n", debug_str, get_time() - time);	// debug term

	render_hud(env);

	// mlx
	// dprintf(2, "%s\n", debug_str);														// debug term
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	sprintf(fps_str, "FPS: %3d", (int)(1 / env->frame_time));
	mlx_string_put(env->mlx, env->win, 10, 20, 0x00FFFFFF, fps_str);
	return (0);
}
