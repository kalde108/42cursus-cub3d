#include "cub3d.h"
#include "key_index.h"

int	focusout_hook(t_c3_env *env)
{
	int	i;

	i = 0;
	while (i < KEY_COUNT)
	{
		env->key_state[i] = 0;
		i++;
	}
	return (0);
}