#include "mlx.h"
#include "render.h"

int	render(t_c3_env *env)
{
	env->frame_time = get_elapsed_time(&env->frame_timer);
	start_timer(&env->frame_timer);
	updates(env);
	if (screen_raycast(env))
		mlx_loop_end(env->mlx);
	if (render_backgound(env))
		mlx_loop_end(env->mlx);
	if (render_wall(env))
		mlx_loop_end(env->mlx);
	hud(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	if (env->options.fps)
		display_fps(env);
	return (0);
}
