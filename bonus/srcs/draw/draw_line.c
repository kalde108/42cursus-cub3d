#include "cub3d.h"
#include "draw.h"

void	draw_line_low(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;
	int	x;

	dx = x2 - x1;
	dy = y2 - y1;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	y = y1;
	x = x1;
	while (x <= x2)
	{
		put_pixel(img, x, y, color);
		if (d > 0)
		{
			y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		x++;
	}
}

void	draw_line_high(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	y;
	int	x;

	dx = x2 - x1;
	dy = y2 - y1;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	y = y1;
	x = x1;
	while (y <= y2)
	{
		put_pixel(img, x, y, color);
		if (d > 0)
		{
			x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		y++;
	}
}

void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;

	dx = (x2 - x1 >= 0) ? x2 - x1 : x1 - x2;
	dy = (y2 - y1 >= 0) ? y2 - y1 : y1 - y2;
	if (dy < dx)
	{
		if (x1 > x2)
			draw_line_low(img, x2, y2, x1, y1, color);
		else
			draw_line_low(img, x1, y1, x2, y2, color);
	}
	else
	{
		if (y1 > y2)
			draw_line_high(img, x2, y2, x1, y1, color);
		else
			draw_line_high(img, x1, y1, x2, y2, color);
	}
}
