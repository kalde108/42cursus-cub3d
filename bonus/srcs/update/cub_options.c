#include "cub3d.h"

static void	op_minimap(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_M])
	{
		if (true == key_release)
			env->options.minimap = !env->options.minimap;
		key_release = false;
	}
	else
		key_release = true;
}

static void	op_minimap_lock(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_L])
	{
		if (true == key_release)
			env->options.minimap_lock = !env->options.minimap_lock;
		key_release = false;
	}
	else
		key_release = true;
}

void	cub_options(t_c3_env *env)
{
	op_minimap(env);
	op_minimap_lock(env);
}
