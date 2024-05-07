#include "mlx.h"
#include "cub3d.h"
#include "key_index.h"

#include <X11/Xutil.h>

int	keydown_hook(int keycode, t_c3_env *env)
{
	int	keyindex;

	if (keycode == XK_Escape)
		mlx_loop_end(env->mlx);
	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
		env->key_state[keyindex] = 1;
	return (0);
}
