#include "mlx.h"
#include "cub3d.h"

static void	update_x(t_c3_env *env, int x)
{
	env->mouse.delta.x = x - env->mouse.x;
	if (x < 1)
	{
		mlx_mouse_move(env->mlx, env->win, WIDTH - 2, env->mouse.y);
		env->mouse.x = WIDTH - 2;
	}
	else if (x >= WIDTH - 1)
	{
		mlx_mouse_move(env->mlx, env->win, 1, env->mouse.y);
		env->mouse.x = 1;
	}
	else
		env->mouse.x = x;
}

static void	update_y(t_c3_env *env)
{
	if (env->mouse.y < 1)
	{
		mlx_mouse_move(env->mlx, env->win, env->mouse.x, HEIGHT - 2);
		env->mouse.y = HEIGHT - 2;
	}
	else if (env->mouse.y >= HEIGHT - 1)
	{
		mlx_mouse_move(env->mlx, env->win, env->mouse.x, 1);
		env->mouse.y = 1;
	}
}

void	update_mouse(t_c3_env *env)
{
	int	x;

	mlx_mouse_get_pos(env->mlx, env->win, &x, &env->mouse.y);
	update_x(env, x);
	update_y(env);
}
