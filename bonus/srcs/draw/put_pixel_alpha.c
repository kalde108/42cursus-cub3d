#include "cub3d.h"

void	put_pixel_alpha(t_img *img, int x, int y, int color)
{
	char	*dst;
	float	alpha;
	int		tmp;
	int		r;
	int		g;
	int		b;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	tmp = *(unsigned int *)dst;
	alpha = (color >> 24) / 255.0;
	r = (int)((((color & 0x00FF0000) >> 16) - ((tmp & 0x00FF0000) >> 16)) * alpha) << 16;
	g = (int)((((color & 0x0000FF00) >> 8) - ((tmp & 0x0000FF00) >> 8)) * alpha) << 8;
	b = (int)((color & 0x000000FF) - (tmp & 0x000000FF)) * alpha;
	*(unsigned int *)dst = tmp + r + g + b;
}
