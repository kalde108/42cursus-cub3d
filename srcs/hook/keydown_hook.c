#include "mlx.h"
#include "cub3d.h"
#include <X11/Xutil.h>

# include <stdio.h>

int	keydown_hook(int keycode, t_c3_env *env)
{
	if (keycode == XK_Escape)
		mlx_loop_end(env->mlx);
	else if (keycode == XK_w)
	{
		printf("W\n");
		env->key_state[22] = 1;
	}
	else if (keycode == XK_a)
	{
		printf("A\n");
		env->key_state[0] = 1;
	}
	else if (keycode == XK_s)
	{
		printf("S\n");
		env->key_state[18] = 1;
	}
	else if (keycode == XK_d)
	{
		printf("D\n");
		env->key_state[3] = 1;
	}
	else
		printf("keycode: %d\n", keycode);
	return (0);
}
