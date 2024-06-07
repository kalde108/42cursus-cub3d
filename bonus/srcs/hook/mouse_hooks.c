
#include <X11/Xutil.h>

#include "cub3d.h"
#include "mlx.h"

# include <stdio.h>

int	buttonpress_hook(int button, int x, int y, t_c3_env *env)
{
	if (Button1 == button)
	{
		env->mouse.status = !env->mouse.status;
		mlx_mouse_move(env->mlx, env->win, WIDTH / 2, HEIGHT / 2);
		env->mouse.x = WIDTH / 2;
		env->mouse.y = HEIGHT / 2;
		env->mouse.delta = 0;
		if (env->mouse.status)
			mlx_mouse_hide(env->mlx, env->win);
		else
			mlx_mouse_show(env->mlx, env->win);
	}
	// if (Button3 == button)
	// {

	// }
	return (0);
	(void)x;
	(void)y;
}
