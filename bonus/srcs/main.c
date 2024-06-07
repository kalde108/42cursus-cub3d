#include "mlx.h"
#include "cub3d.h"

# include <stdlib.h>
# include <stdio.h>

int	g_debug = 0;

void DISPLAY_SHORT_MAP(t_c3_env *env); //REMOVE

int	main(int ac, char **av)
{
	t_c3_env	env;

	srand(time(NULL));
	env = (t_c3_env){0};
	if (check_arguments(ac, av) || init_cubenv(&env, av[1]))
		return (1);
	if (load_textures(env.mlx, env.scene.elems) || open_mlx_window(&env))
	{
		destroy_cubenv(&env);
		return (1);
	}
	if (pthread_mutex_init(&env.call_mutex, NULL))
	{
		destroy_cubenv(&env);
		return (1);
	}
	DISPLAY_SHORT_MAP(&env);
	mlx_loop(env.mlx);
	destroy_cubenv(&env);
	pthread_mutex_destroy(&env.call_mutex);
	return (0);
}
