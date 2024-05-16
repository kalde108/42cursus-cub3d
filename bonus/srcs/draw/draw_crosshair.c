#include "cub3d.h"
#include "draw.h"

static inline void 	vbar(uint32_t *dst, t_v2d_i center, t_v2d_i size)
{
	int		x;
	int		y;
	t_color	color;

	y = center.y - (size.y >> 1);
	while (y < center.y + (size.y >> 1))
	{
		x = center.x - (size.x >> 1);
		while (x < center.x + (size.x >> 1))
		{
			color.argb = dst[(y << WIDTH_LOG2) + x];
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
			dst[(y << WIDTH_LOG2) + x] = color.argb;
			x++;
		}
		y++;
	}
}

static inline void	hbar(uint32_t *dst, t_v2d_i center, t_v2d_i size)
{
	int		x;
	int		y;
	t_color	color;

	y = center.y - (size.x >> 1);
	while (y < center.y + (size.x >> 1))
	{
		x = center.x - (size.y >> 1);
		while (x < center.x + (size.y >> 1))
		{
			if (x >= center.x - (size.x >> 1) && x <= center.x + (size.x >> 1) - 1)
			{
				x++;
				continue ;
			}
			color.argb = dst[(y << WIDTH_LOG2) + x];
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
			dst[(y << WIDTH_LOG2) + x] = color.argb;
			x++;
		}
		y++;
	}
}

void	draw_crosshair(t_c3_env *env)
{
	unsigned int	*dst;
	t_v2d_i			center;
	t_v2d_i			size;

	center.x = WIDTH >> 1;
	center.y = HEIGHT >> 1;
	size.x = 3;
	size.y = 20;
	dst = (unsigned int *)env->img.addr;
	vbar(dst, center, size);
	hbar(dst, center, size);
}
