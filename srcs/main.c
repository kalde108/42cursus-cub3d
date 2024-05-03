#include "mlx.h"
#include "mlx_tools.h"
#include "cub3d.h"
#include <X11/Xutil.h>

# include <unistd.h>
# include <stdio.h>

int main(void)
{
	t_c3_env	env;

	env = (t_c3_env){0};
	env.pos = (t_v2d_d){22, 12};
	env.dir = (t_v2d_d){-1, 0};
	env.plane = (t_v2d_d){0, 0.66};
	env.move_speed = 0.03;
	env.rot_speed = 0.01;
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
	return (0);
}
