#include "draw.h"
#include <math.h>

void	mini_player(t_img *img, double angle, t_minimap *minimap)
{
	t_v2d_d	a;
	t_v2d_d	b;
	t_v2d_d	c;
	t_v2d_d	d;
	t_v2d_d	center;

	center = (t_v2d_d){minimap->pos.x, minimap->pos.y};
	a = (t_v2d_d){center.x, center.y - minimap->zoom / 2};
	b = (t_v2d_d){center.x - minimap->zoom / 2, center.y + minimap->zoom / 2};
	c = (t_v2d_d){center.x, center.y + minimap->zoom / 3};
	d = (t_v2d_d){center.x + minimap->zoom / 2, center.y + minimap->zoom / 2};
	if (minimap->lock)
	{
		ft_rotate_v2_around(&a, angle, (t_v2d_d){center.x, center.y});
		ft_rotate_v2_around(&b, angle, (t_v2d_d){center.x, center.y});
		ft_rotate_v2_around(&c, angle, (t_v2d_d){center.x, center.y});
		ft_rotate_v2_around(&d, angle, (t_v2d_d){center.x, center.y});
	}
	a = (t_v2d_d){floor(a.x), floor(a.y)};
	b = (t_v2d_d){floor(b.x), floor(b.y)};
	c = (t_v2d_d){floor(c.x), floor(c.y)};
	d = (t_v2d_d){floor(d.x), floor(d.y)};
	draw_triangle(img, (t_triangle){a, b, c}, (t_color){0x65e004});
	draw_triangle(img, (t_triangle){a, c, d}, (t_color){0x52af08});
}
