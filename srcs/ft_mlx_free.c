#include "mlx.h"
#include "cub3d.h"

#include <stdlib.h>

void	ft_mlx_free(t_c3_env *env)
{
	if (env->img.img)
		mlx_destroy_image(env->mlx, env->img.img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	if (env->mlx)
		free(env->mlx);
}
