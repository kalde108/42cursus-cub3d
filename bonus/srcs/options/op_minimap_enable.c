#include "cub3d.h"

void	op_minimap_enable(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_M])
	{
		if (true == key_release)
		{
			env->options.minimap.enable = !env->options.minimap.enable;
		}
		key_release = false;
	}
	else
		key_release = true;
}
