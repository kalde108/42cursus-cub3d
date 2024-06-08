
#include <X11/Xutil.h>

#include "cub3d.h"
#include "mlx.h"
#include "minimap.h"

int	buttonpress_hook(int button, int x, int y, t_c3_env *env)
{
	(void)x;
	(void)y;
	if (Button1 == button && !(env->mouse.status & MOUSE_BUTTON_RIGHT))
	{
		if (env->mouse.status & MOUSE_BUTTON_LEFT)
			env->mouse.status &= ~MOUSE_BUTTON_LEFT;
		else
			env->mouse.status |= MOUSE_BUTTON_LEFT;
		mlx_mouse_move(env->mlx, env->win, WIDTH / 2, HEIGHT / 2);
		env->mouse.x = WIDTH / 2;
		env->mouse.y = HEIGHT / 2;
		env->mouse.delta.x = 0;
		if (env->mouse.status)
			mlx_mouse_hide(env->mlx, env->win);
		else
			mlx_mouse_show(env->mlx, env->win);
	}
	if (Button3 == button && !(env->mouse.status & MOUSE_BUTTON_LEFT))
	{
		if (!is_on_minimap(&env->options.minimap, x, y))
			return (0);
		if (env->mouse.status & MOUSE_BUTTON_RIGHT)
			env->mouse.status &= ~MOUSE_BUTTON_RIGHT;
		else
			env->mouse.status |= MOUSE_BUTTON_RIGHT;
		env->mouse.x = x;
		env->mouse.y = y;
		env->mouse.delta = (t_v2d_i){0, 0};
	}
	return (0);
}

int	buttonrelease_hook(int button, int x, int y, t_c3_env *env)
{
	(void)x;
	(void)y;
	if (Button3 == button && env->mouse.status & MOUSE_BUTTON_RIGHT)
		env->mouse.status &= ~MOUSE_BUTTON_RIGHT;
	return (0);
}
