#include "mlx.h"
#include "mlx_tools.h"
#include "cub3d.h"
#include <X11/Xutil.h>

# include <unistd.h>
# include <stdio.h>

char	**test_map;

void 		DEBUG_PRINT_MAP(t_cubscene scene); //REMOVE

int main(int ac, char **av)
{
	t_c3_env	env;

	env = (t_c3_env){0};
	init_scene(&env.scene);
	if (check_scene_format(av + 1)
		|| get_cubscene(av[1], &env.scene)
		|| get_player_spawn(env.scene, &env.player))
	{
		destroy_scene(&env.scene);
		return (1);
	}
	DEBUG_PRINT_MAP(env.scene);
	printf("\nPLAYER SPAWN(%fx,%fy)\nDIRECTION(%fx,%fy)\n\n", env.player.pos.x, env.player.pos.y, env.player.dir.x, env.player.dir.y);

	// env.player.plane = (t_v2d_d){0, 0.66};
	env.player.mv_speed = 0.03;
	env.player.rt_speed = 0.01;
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
