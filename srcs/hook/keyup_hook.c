#include "mlx.h"
#include "cub3d.h"
#include "key_index.h"

#include <X11/Xutil.h>

# include <stdio.h>

int	keyup_hook(int keycode, t_c3_env *env)
{
	if (keycode == XK_Escape)
		mlx_loop_end(env->mlx);
	else if (keycode == XK_w)
		env->key_state[KEY_W] = 0;
	else if (keycode == XK_a)
		env->key_state[KEY_A] = 0;
	else if (keycode == XK_s)
		env->key_state[KEY_S] = 0;
	else if (keycode == XK_d)
		env->key_state[KEY_D] = 0;
	else if (keycode == XK_Left)
		env->key_state[KEY_LEFT] = 0;
	else if (keycode == XK_Right)
		env->key_state[KEY_RIGHT] = 0;
	else if (keycode == XK_space)
		env->key_state[KEY_SPACE] = 0;
	else
		printf("~keycode: %d\n", keycode);
	return (0);
}
