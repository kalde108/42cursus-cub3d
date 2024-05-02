#include "mlx.h"
#include "cub3d.h"

int	ft_mlx_init(t_c3_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		return (1);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!env->win)
		return (1);
	env->img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img)
		return (1);
	env->img.addr = mlx_get_data_addr(env->img.img,
			&env->img.bits_per_pixel,
			&env->img.line_length,
			&env->img.endian);
	if (!env->img.addr)
		return (1);
	return (0);
}
