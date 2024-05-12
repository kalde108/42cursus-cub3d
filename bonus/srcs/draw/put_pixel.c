#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	((int *)img->addr)[(y << WIDTH_LOG2) + x] = color;
}
