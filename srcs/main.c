#include "mlx.h"
#include "mlx_tools.h"
#include "cub3d.h"
#include <X11/Xutil.h>

void		DEBUG_PRINT_MAP(t_cubscene scene);	//REMOVE
void		DEBUG_print(t_cubscene *ptr);	//REMOVE

int	main(int ac, char **av)
{
	t_c3_env	env;

	env = (t_c3_env){0};
	if (check_arguments(ac, av) || init_cubenv(&env, av[1]))
		return (1);
	DEBUG_print(&env.scene);
	DEBUG_PRINT_MAP(env.scene); //REMOVE
	if (load_textures(env.mlx, &env.scene) || open_mlx_window(&env))
	{
		destroy_cubenv(&env);
		return (1);
	}
	mlx_loop(env.mlx);
	destroy_cubenv(&env);
	return (0);
}
