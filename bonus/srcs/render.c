#include "mlx.h"
#include "render.h"
#include "draw.h"
#include "update.h"

# include "minimap.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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
	// char	debug_str[10000];															// debug term

	// usleep(100000);	// fake load
	env->frame_time = get_elapsed_time(&env->frame_timer);
	start_timer(&env->frame_timer);
	// sprintf(debug_str, "Stats:\n");														// debug term

	// updates
	// time = get_time();																	// debug term
	if (env->mouse.status == MOUSE_BUTTON_LEFT)
		update_mouse(env);
	// sprintf(debug_str, "%supdate_mouse: %3zums\n", debug_str, get_time() - time);		// debug term
	update_player(env);
	// time = get_time();																	// debug term
	update_frames(env);
	player_interaction(env);
	cub_options(env);
	// sprintf(debug_str, "%sframe_updates: %3zums\n", debug_str, get_time() - time);		// debug term

	// time = get_time();																	// debug term
	if (screen_raycast(env))
		mlx_loop_end(env->mlx);
	// sprintf(debug_str, "%sscreen_raycast: %3zums\n", debug_str, get_time() - time);		// debug term

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
	hud(env);
	// sprintf(debug_str, "%shud: %3zums\n", debug_str, get_time() - time);			// debug term

	// mlx
	// dprintf(2, "%s\n", debug_str);														// debug term
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	if (env->options.fps)
		display_fps(env);
	return (0);
}
