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

static void	op_minimap_zoom(t_c3_env *env)
{
	// static bool	key_release = true;

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

static void	op_minimap_pos(t_c3_env *env)
{
	if (env->mouse.status)
		return ;
	// mlx_mouse_get_pos(env->mlx, env->win, &x, &env->mouse.y);
	// if ()
}

void	cub_options(t_c3_env *env)
{
	op_minimap(env);
	op_minimap_lock(env);
	op_minimap_zoom(env);
	op_minimap_pos(env);
	op_debug(env);
}
