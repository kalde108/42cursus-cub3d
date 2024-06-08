#include "mlx.h"
#include "render.h"

# include <stdio.h>

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
	updates(env);
	// sprintf(debug_str, "%supdates: %3zums\n", debug_str, get_time() - time);				// debug term

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
