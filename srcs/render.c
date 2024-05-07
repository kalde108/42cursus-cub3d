#include "mlx.h"
#include "render.h"
#include "draw.h"

int	render(t_c3_env *env)
{
	floor_and_ceiling(env);
	update_player(env);
	simple_raycasting(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
