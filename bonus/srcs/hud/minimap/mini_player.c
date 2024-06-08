#include "cub3d.h"

void	draw_player(t_c3_env *env, double angle)
{
	t_v2d_d	a;
	t_v2d_d	b;
	t_v2d_d	c;
	t_v2d_d	d;

	a = (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y - env->options.minimap.zoom / 2};
	b = (t_v2d_d){env->options.minimap.pos.x - env->options.minimap.zoom / 2, env->options.minimap.pos.y + env->options.minimap.zoom / 2};
	c = (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y + env->options.minimap.zoom / 3};
	d = (t_v2d_d){env->options.minimap.pos.x + env->options.minimap.zoom / 2, env->options.minimap.pos.y + env->options.minimap.zoom / 2};
	if (env->options.minimap.lock)
	{
		ft_rotate_v2_around(&a, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
		ft_rotate_v2_around(&b, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
		ft_rotate_v2_around(&c, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
		ft_rotate_v2_around(&d, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
	}
	a = (t_v2d_d){floor(a.x), floor(a.y)};
	b = (t_v2d_d){floor(b.x), floor(b.y)};
	c = (t_v2d_d){floor(c.x), floor(c.y)};
	d = (t_v2d_d){floor(d.x), floor(d.y)};
	draw_triangle(&env->img, (t_triangle){a, b, c}, (t_color){0x65e004});
	draw_triangle(&env->img, (t_triangle){a, c, d}, (t_color){0x52af08});
}