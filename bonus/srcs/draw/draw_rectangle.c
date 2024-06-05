#include "cub3d.h"

void	draw_rectangle(t_img *img, t_v2d_i pos, t_v2d_i size, t_color color)
{
	int	x;
	int	y;
	t_v2d_i half_size;

	half_size.x = size.x >> 1;
	half_size.y = size.y >> 1;
	y = pos.y - half_size.y;
	while (y < pos.y + half_size.y)
	{
		x = pos.x - half_size.x;
		while (x < pos.x + half_size.x)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				img->addr[(y << WIDTH_LOG2) + x] = color;
			x++;
		}
		y++;
	}
}
