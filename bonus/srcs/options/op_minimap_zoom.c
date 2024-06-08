#include "cub3d.h"

void	op_minimap_zoom(t_c3_env *env)
{
	if (!env->key_state[KEY_CTRL_L])
	{
		if (env->key_state[KEY_KP_ADD])
		{
			if (env->options.minimap.zoom < 50.0)
				env->options.minimap.zoom *= 1.01;
		}
		if (env->key_state[KEY_KP_SUB])
		{
			if (env->options.minimap.zoom > 1.0)
				env->options.minimap.zoom *= 0.99;
		}
	}
}
