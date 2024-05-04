#include "cub3d.h"

int	get_color(char type, t_v2d_d ray_dir, int side, double perp_wall_dist)
{
		int color;
		float	alpha;
		int	r;
		int	g;
		int	b;

		// alpha = 1 - perp_wall_dist / 20;
		// if (alpha < 0)
		// 	alpha = 0;
		(void)perp_wall_dist;
		alpha = 1;

		if (type == '1')
			color = 0x00FF0000;
		// else if (type == 2)
		// 	color = 0x0000FF00;
		// else if (type == 3)
		// 	color = 0x000000FF;
		// else if (type == 4)
		// 	color = 0x00FFFF00;
		else
			color = 0x00FFFFFF;
	
		if (side == 0)
		{
			r = (color >> 16) & 0x000000FF;
			g = (color >> 8) & 0x000000FF;
			b = color & 0x000000FF;
			if (ray_dir.x > 0)
				color = ((int)(r / 3 * alpha) << 16) + ((int)(g / 3 * alpha) << 8) + (int)(b / 3 * alpha);
				// color = (r / 3 << 16) + (g / 3 << 8) + b / 3;
			else if (ray_dir.x < 0)
				color = ((int)(r / 2 * alpha) << 16) + ((int)(g / 2 * alpha) << 8) + (int)(b / 2 * alpha);
				// color = (r / 2 << 16) + (g / 2 << 8) + b / 2;
		}
		else if (ray_dir.y < 0)
		{
			r = (color >> 16) & 0x000000FF;
			g = (color >> 8) & 0x000000FF;
			b = color & 0x000000FF;
			color = ((int)(r / 4 * alpha) << 16) + ((int)(g / 4 * alpha) << 8) + (int)(b / 4 * alpha);
			// color = (r / 4 << 16) + (g / 4 << 8) + b / 4;
		}
		else if (ray_dir.y > 0)
		{
			r = (color >> 16) & 0x000000FF;
			g = (color >> 8) & 0x000000FF;
			b = color & 0x000000FF;
			color = ((int)(r * alpha) << 16) + ((int)(g * alpha) << 8) + (int)(b * alpha);
			// color = (r << 16) + (g << 8) + b;
		}


		// alpha = (int)(255 * (1 - perp_wall_dist / 20));
		// if (alpha < 0)
		// 	alpha = 0;

		// // color = (color & 0x00FFFFFF) | (alpha << 24);
		// color += 0xFF000000;

		// if (test_map[map_pos.y][map_pos.x])
		// {
		// 	r = 255 * perp_wall_dist / 20;
		// 	if (r > 255)
		// 		r = 255;
		// 	g = 0;
		// 	b = 255 - r;
		// 	color = (r << 16) + (g << 8) + b;
		// }
		// else
		// {
		// 	// color = 0;
		// 	color = 0x00FFFFFF;
		// }

		return (color);
}
