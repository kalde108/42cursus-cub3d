#include "cub3d.h"

#include <stdio.h>

int	get_color(char type, t_v2d_d ray_dir, int side, double perp_wall_dist)
{
		int color;
		float	alpha;
		int	r;
		int	g;
		int	b;

		(void)perp_wall_dist;
		alpha = 1;

		if (type == '1')
			color = 0x00FF0000;
		else
			color = 0x00FFFFFF;
	
		if (side == 0)
		{
			r = (color >> 16) & 0x000000FF;
			g = (color >> 8) & 0x000000FF;
			b = color & 0x000000FF;
			if (ray_dir.x > 0)
				color = ((int)(r / 3 * alpha) << 16) + ((int)(g / 3 * alpha) << 8) + (int)(b / 3 * alpha);
			else if (ray_dir.x < 0)
				color = ((int)(r / 2 * alpha) << 16) + ((int)(g / 2 * alpha) << 8) + (int)(b / 2 * alpha);
		}
		else if (ray_dir.y < 0)
		{
			r = (color >> 16) & 0x000000FF;
			g = (color >> 8) & 0x000000FF;
			b = color & 0x000000FF;
			color = ((int)(r / 4 * alpha) << 16) + ((int)(g / 4 * alpha) << 8) + (int)(b / 4 * alpha);
		}
		else if (ray_dir.y > 0)
		{
			r = (color >> 16) & 0x000000FF;
			g = (color >> 8) & 0x000000FF;
			b = color & 0x000000FF;
			color = ((int)(r * alpha) << 16) + ((int)(g * alpha) << 8) + (int)(b * alpha);
		}

		return (color);
}
