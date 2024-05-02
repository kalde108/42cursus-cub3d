#include "mlx.h"
#include "cub3d.h"
#include "draw.h"
#include "key_index.h"

int	render(t_c3_env *env)
{
	clean_screen(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
