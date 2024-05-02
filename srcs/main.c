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
	env.posX = 22;
	env.posY = 12;
	env.dirX = -1;
	env.dirY = 0;
	env.planeX = 0;
	env.planeY = 0.66;
	env.time = 0;
	env.oldTime = 0;
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
