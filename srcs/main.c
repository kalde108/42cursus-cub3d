#include "mlx.h"
#include "mlx_tools.h"
#include "cub3d.h"
#include <X11/Xutil.h>

# include <unistd.h>
# include <stdio.h>

int main(int ac, char **av)
{
	t_c3_env	env;

	env = (t_c3_env){0};
	init_scene(&env.scene);
	int status = check_scene_format(av + 1) || get_cubscene(av[1], &env.scene);
	// DEBUG_print(&scene);
	if (status)
	{
		destroy_scene(&env.scene);
		return (1);
	}

	if (ft_mlx_init(&env))
	{
		ft_mlx_free(&env);
		return (1);
	}
	mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &mlx_loop_end, env.mlx);
	mlx_hook(env.win, KeyPress, KeyPressMask, &keydown_hook, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, &keyup_hook, &env);
	mlx_loop_hook(env.mlx, &render, &env);
	mlx_loop(env.mlx);
	ft_mlx_free(&env);
	destroy_scene(&env.scene);
	return (0);
	(void)ac;
}
