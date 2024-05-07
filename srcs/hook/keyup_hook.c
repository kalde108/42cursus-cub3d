#include "mlx.h"
#include "cub3d.h"
#include "key_index.h"

int	keyup_hook(int keycode, t_c3_env *env)
{
	int	keyindex;

	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
		env->key_state[keyindex] = 0;
	return (0);
}
