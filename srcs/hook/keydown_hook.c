#include "mlx.h"
#include "cub3d.h"
#include "key_index.h"

#include <X11/Xutil.h>

# include <stdio.h>

int	keydown_hook(int keycode, t_c3_env *env)
{
	if (keycode == XK_Escape)
		mlx_loop_end(env->mlx);
	else if (keycode == XK_w)
	{
		printf("W\n");
		env->key_state[KEY_W] = 1;
	}
	else if (keycode == XK_a)
	{
		printf("A\n");
		env->key_state[KEY_A] = 1;
	}
	else if (keycode == XK_s)
	{
		printf("S\n");
		env->key_state[KEY_S] = 1;
	}
	else if (keycode == XK_d)
	{
		printf("D\n");
		env->key_state[KEY_D] = 1;
	}
	else if (keycode == XK_space)
	{
		printf("SPACE\n");
		env->key_state[KEY_SPACE] = 1;
	}
	else
		printf("keycode: %d\n", keycode);
	return (0);
}
