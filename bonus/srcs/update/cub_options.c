#include "cub3d.h"
#include "minimap.h"

static void	op_minimap_status(t_c3_env *env)
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

static void	op_fps(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_F])
	{
		if (true == key_release)
			env->options.fps = !env->options.fps;
		key_release = false;
	}
	else
		key_release = true;
}

static void	op_minimap_zoom(t_c3_env *env)
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

#include "mlx.h"
static void	op_minimap_pos(t_c3_env *env)
{
	t_v2d_i	pos;

	if (!(env->mouse.status & MOUSE_BUTTON_RIGHT)
		|| !env->options.minimap.enable)
		return ;
	mlx_mouse_get_pos(env->mlx, env->win, &pos.x, &pos.y);
	if (env->mouse.x == pos.x && env->mouse.y == pos.y)
		return ;
	env->mouse.x = pos.x;
	env->mouse.y = pos.y;
	if (pos.x < env->options.minimap.size >> 1)
		pos.x = env->options.minimap.size >> 1;
	if (pos.x >= WIDTH - (env->options.minimap.size >> 1))
		pos.x = WIDTH - 1 - (env->options.minimap.size >> 1);
	if (pos.y < env->options.minimap.size >> 1)
		pos.y = env->options.minimap.size >> 1;
	if (pos.y >= HEIGHT - (env->options.minimap.size >> 1))
		pos.y = HEIGHT - 1 - (env->options.minimap.size >> 1);
	env->options.minimap.pos = pos;
}

static void	op_minimap_size(t_c3_env *env)
{
	if (env->key_state[KEY_CTRL_L])
	{
		if (env->key_state[KEY_KP_ADD])
		{
			if (env->options.minimap.size < HEIGHT)
				env->options.minimap.size += 1;
		}
		if (env->key_state[KEY_KP_SUB])
		{
			if (env->options.minimap.size > 100.0)
				env->options.minimap.size -= 1;
		}
	}
	if (env->options.minimap.pos.x < env->options.minimap.size >> 1)
		env->options.minimap.pos.x += 1;
	if (env->options.minimap.pos.x >= WIDTH - (env->options.minimap.size >> 1))
		env->options.minimap.pos.x -= 1;
	if (env->options.minimap.pos.y < env->options.minimap.size >> 1)
		env->options.minimap.pos.y += 1;
	if (env->options.minimap.pos.y >= HEIGHT - (env->options.minimap.size >> 1))
		env->options.minimap.pos.y -= 1;
}

static void	op_minimap_view(t_c3_env *env)
{
	static bool	key_release = true;

	if (env->key_state[KEY_V])
	{
		if (true == key_release)
			env->options.minimap.view = !env->options.minimap.view;
		key_release = false;
	}
	else
		key_release = true;
}

void	cub_options(t_c3_env *env)
{
	op_minimap_status(env);
	op_minimap_lock(env);
	op_minimap_zoom(env);
	op_minimap_pos(env);
	op_minimap_size(env);
	op_minimap_view(env);
	op_fps(env);
}
