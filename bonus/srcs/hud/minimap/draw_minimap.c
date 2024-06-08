#include "cub3d.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

# include <math.h>
# include <stdio.h>

// void	draw_border(t_c3_env *env)
// {
// 	int	half_size;

// 	half_size = env->options.minimap.size >> 1;
// 	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x, env->options.minimap.pos.y - half_size - 2}, (t_v2d_i){env->options.minimap.size + 4, 2}, MINIMAP_BORDER_COLOR);
// 	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x, env->options.minimap.pos.y + half_size + 1}, (t_v2d_i){env->options.minimap.size + 4, 2}, MINIMAP_BORDER_COLOR);
// 	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x - half_size - 2, env->options.minimap.pos.y}, (t_v2d_i){2, env->options.minimap.size + 4}, MINIMAP_BORDER_COLOR);
// 	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x + half_size + 1, env->options.minimap.pos.y}, (t_v2d_i){2, env->options.minimap.size + 4}, MINIMAP_BORDER_COLOR);
// }

void	draw_minimap(t_c3_env *env)
{
	double	angle;

	angle = player_angle(env->player.camera.dir);
	mini_scene(env, angle);
	if (env->options.minimap.view)
		draw_view_cone(env, -angle);
	mini_player(&env->img, angle, &env->options.minimap);
}
