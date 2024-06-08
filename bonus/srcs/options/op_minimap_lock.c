#include "cub3d.h"

void	op_minimap_lock(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_L])
	{
		if (true == key_release)
			env->options.minimap.lock = !env->options.minimap.lock;
		key_release = false;
	}
	else
		key_release = true;
}
