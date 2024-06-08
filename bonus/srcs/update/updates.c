#include "update.h"

void	updates(t_c3_env *env)
{
	if (env->mouse.status == MOUSE_BUTTON_LEFT)
		update_mouse(env);
	update_player(env);
	update_frames(env);
	player_interaction(env);
	cub_options(env);
}
