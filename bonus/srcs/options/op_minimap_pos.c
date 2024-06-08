#include "cub3d.h"
#include "mlx.h"

void	op_minimap_pos(t_c3_env *env)
{
	t_v2d_i	pos;

	if (!(env->mouse.status & MOUSE_BUTTON_RIGHT)
		|| !env->options.minimap.enable)
		return ;
	mlx_mouse_get_pos(env->mlx, env->win, &pos.x, &pos.y);
	if (env->mouse.x == pos.x && env->mouse.y == pos.y)
		return ;
	env->mouse.x = pos.x;
	env->mouse.y = pos.y;
	if (pos.x < env->options.minimap.size >> 1)
		pos.x = env->options.minimap.size >> 1;
	if (pos.x >= WIDTH - (env->options.minimap.size >> 1))
		pos.x = WIDTH - 1 - (env->options.minimap.size >> 1);
	if (pos.y < env->options.minimap.size >> 1)
		pos.y = env->options.minimap.size >> 1;
	if (pos.y >= HEIGHT - (env->options.minimap.size >> 1))
		pos.y = HEIGHT - 1 - (env->options.minimap.size >> 1);
	env->options.minimap.pos = pos;
}
