#include "mlx.h"
#include "render.h"
#include "draw.h"

int	render(t_c3_env *env)
{
	// printf("render\n");
	// clean_screen(env);
	floor_and_ceiling(env);

	update_player(env);

	simple_raycasting(env);

	draw_minimap(env);

	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	// mlx_put_image_to_window(env->mlx, env->win, env->scene.texture->ptr, 0, 0);
	return (0);
}
