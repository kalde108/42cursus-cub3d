
#include <X11/Xutil.h>

#include "cub3d.h"
#include "mlx.h"

int buttonpress_hook(int button, int x, int y, t_c3_env *env)
{
	(void)x;
	if (Button1 == button)
	{
		env->mouse.status = true;
		env->mouse.x = x;
		env->mouse.y = y;
	}
	return (0);
	(void)y;
}

int buttonrelease_hook(int button, int x, int y, t_c3_env *env)
{
	if (Button1 == button)
	{
		env->mouse.status = false;
		env->mouse.x = 0;
		env->mouse.delta = 0;
	}
	return (0);
	(void)x;
	(void)y;
}

int mousemotion_hook(int x, int y, t_c3_env *env)
{
	if (true == env->mouse.status)
	{
		env->mouse.delta = x - env->mouse.x;
		env->mouse.x = x;
	}
	return (0);
	(void)y;
}
