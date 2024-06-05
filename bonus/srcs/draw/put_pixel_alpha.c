#include "cub3d.h"

void	put_pixel_alpha(t_img *img, int x, int y, t_color color)
{
	t_color	*dst;
	t_color tmp;
	float	alpha;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y << WIDTH_LOG2) + x;
	tmp = *dst;
	alpha = (float)color.a / 255.0;
	dst->r += (color.r - tmp.r) * alpha;
	dst->g += (color.g - tmp.g) * alpha;
	dst->b += (color.b - tmp.b) * alpha;
}
