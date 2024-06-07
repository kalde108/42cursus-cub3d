#include "cub3d.h"

static void	op_minimap(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_M])
	{
		if (true == key_release)
			env->options.minimap.enable = !env->options.minimap.enable;
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
			env->options.minimap.lock = !env->options.minimap.lock;
		key_release = false;
	}
	else
		key_release = true;
}

static void	op_debug(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_P])
	{
		if (true == key_release)
			env->options.debug = !env->options.debug;
		key_release = false;
	}
	else
		key_release = true;
}

void	cub_options(t_c3_env *env)
{
	op_minimap(env);
	op_minimap_lock(env);
	op_debug(env);
}
