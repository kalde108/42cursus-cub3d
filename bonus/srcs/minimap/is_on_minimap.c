#include "cub3d.h"
#include "minimap.h"

int	is_on_minimap(t_c3_env *env, int x, int y)
{
	t_v2d_i	top_left;
	t_v2d_i	bottom_right;

	if (!env->options.minimap.enable)
		return (0);
	top_left = (t_v2d_i){env->options.minimap.pos.x - (env->options.minimap.size >> 1),
						env->options.minimap.pos.y - (env->options.minimap.size >> 1)};
	bottom_right = (t_v2d_i){env->options.minimap.pos.x + (env->options.minimap.size >> 1),
							env->options.minimap.pos.y + (env->options.minimap.size >> 1)};
	return (x >= top_left.x && x <= bottom_right.x
			&& y >= top_left.y && y <= bottom_right.y);
}
