#include "cub3d.h"

void	draw_rectangle(t_img *img, t_v2d_i pos, t_v2d_i size, int color)
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
			*(unsigned int *)(img->addr + ((y << img->line_length) + x * (img->bits_per_pixel / 8))) = color;
			x++;
		}
		y++;
	}
}
