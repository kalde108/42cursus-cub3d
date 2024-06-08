#include "mlx.h"
#include "render.h"
#include "draw.h"
#include "update.h"

# include "minimap.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

static int	get_average_fps(size_t frame_time);

static void	update_mouse(t_c3_env *env)
{
	int	x;

	mlx_mouse_get_pos(env->mlx, env->win, &x, &env->mouse.y);
	env->mouse.delta.x = x - env->mouse.x;
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

void	draw_interaction_cooldown(t_c3_env *env)
{
	size_t	cooldown;

	cooldown = get_elapsed_time(&env->player.interact);
	if (cooldown > INTERACTION_COOLDOWN)
		return ;
	if (env->player.succesful_interact)
		draw_rectangle(&env->img, (t_v2d_i){WIDTH / 2 + 20, HEIGHT / 2 + 10 - (20 * cooldown / INTERACTION_COOLDOWN / 2)}, (t_v2d_i){4, 20 * cooldown / INTERACTION_COOLDOWN}, (t_color){0x00AAAAAA});
	else
		draw_rectangle(&env->img, (t_v2d_i){WIDTH / 2 + 20, HEIGHT / 2 + 10 - (20 * cooldown / INTERACTION_COOLDOWN / 2)}, (t_v2d_i){4, 20 * cooldown / INTERACTION_COOLDOWN}, (t_color){0x00FF0000});
}

void	render_hud(t_c3_env *env)
{
	draw_crosshair(env);
	draw_interaction_cooldown(env);
	if (env->options.minimap.enable)
		draw_minimap(env);
}

// # include "raycasting.h"
// # include "tile_address.h"
// void	test_single_raycast(t_c3_env *env)
// {
// 	t_hit_buffer	hit_buf[MAX_LAYERS];

// 	single_raycast(&env->scene, env->player.camera, hit_buf);
// 	dprintf(2, "\nhit_buf->count: %d\n", hit_buf->count);
// 	dprintf(2, "First hit: %X\n", hit_buf[0].cell);
// 		dprintf(2, "\tray.perp_wall_dist: %f\n", hit_buf[0].z);
// 		dprintf(2, "\tcamera.pos: %f, %f\n", hit_buf[0].camera.pos.x, hit_buf[0].camera.pos.y);
// 		dprintf(2, "\tside: %d\n", hit_buf[0].side);
// 	if (IS_PORTAL(hit_buf[0].cell))
// 		dprintf(2, "\tportal hit\n");
// 	else
// 		dprintf(2, "\twall hit\n");
// 	dprintf(2, "Last hit: %X\n", hit_buf[hit_buf->count - 1].cell);
// 		dprintf(2, "\tray.perp_wall_dist: %f\n", hit_buf[hit_buf->count - 1].z);
// 		dprintf(2, "\tcamera.pos: %f, %f\n", hit_buf[hit_buf->count - 1].camera.pos.x, hit_buf[hit_buf->count - 1].camera.pos.y);
// 		dprintf(2, "\tside: %d\n", hit_buf[hit_buf->count - 1].side);
// 	if (IS_PORTAL(hit_buf[hit_buf->count - 1].cell))
// 		dprintf(2, "\tportal hit\n");
// 	else
// 		dprintf(2, "\twall hit\n");
// }

int	render(t_c3_env *env)
{
	// size_t	time;																		// debug term
	char	fps_str[17];
	// char	debug_str[10000];															// debug term

	// usleep(100000);	// fake load
	env->frame_time = get_elapsed_time(&env->frame_timer);
	start_timer(&env->frame_timer);
	// sprintf(debug_str, "FPS: %4.2f\n", 1 / env->frame_time);							// debug term

	// test_single_raycast(env);															// debug term

	// updates
	// time = get_time();																	// debug term
	if (env->mouse.status == MOUSE_BUTTON_LEFT)
		update_mouse(env);
	// sprintf(debug_str, "%supdate_mouse: %3zums\n", debug_str, get_time() - time);		// debug term
	update_player(env);
	update_entities(env);
	// time = get_time();																	// debug term
	update_frames(env);
	player_interaction(env);
	cub_options(env);
	// sprintf(debug_str, "%sframe_updates: %3zums\n", debug_str, get_time() - time);		// debug term

	if (screen_raycast(env))
		mlx_loop_end(env->mlx);

	// rendering
	// time = get_time();																	// debug term
	if (render_backgound(env))
		mlx_loop_end(env->mlx);
	// sprintf(debug_str, "%sfloor_and_ceiling: %3zums\n", debug_str, get_time() - time);	// debug term
	// time = get_time();																	// debug term
	if (render_wall(env))
		mlx_loop_end(env->mlx);
	// sprintf(debug_str, "%srender_map: %3zums\n", debug_str, get_time() - time);			// debug term
	// time = get_time();																	// debug term
	// render_entities(env);
	// sprintf(debug_str, "%srender_entities: %3zums\n", debug_str, get_time() - time);	// debug term

	render_hud(env);

	// mlx
	// dprintf(2, "%s\n", debug_str);														// debug term
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	if (env->options.fps)
	{
		sprintf(fps_str, "FPS: %3d", get_average_fps(env->frame_time));
		mlx_string_put(env->mlx, env->win, 10, 20, 0x00FFFFFF, fps_str);
	}
	return (0);
}

static int	get_average_fps(size_t frame_time)
{
	static size_t	fps[FPS_BUFFER] = {0};
	static int		i = 0;
	size_t			average;
	int				j;

	fps[i++] = frame_time;
	if (i == FPS_BUFFER)
	{
		i = 0;
	}
	j = 0;
	average = 0;
	while (j < FPS_BUFFER)
	{
		average += fps[j++];
	}
	average /= FPS_BUFFER;
	if (0 == average)
		return (0);
	return (1000 / average);
}
