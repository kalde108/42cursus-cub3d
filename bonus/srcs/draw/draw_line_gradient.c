#include "cub3d.h"
#include "draw.h"

#include "cub3d.h"
#include "draw.h"

void	draw_line_low_gradient(t_img *img, int x1, int y1, int x2, int y2, int color1, int color2)
{
	int	dr;
	int	dg;
	int	db;
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;
	int	x;

	dr = (color2 >> 16 & 0xFF) - (color1 >> 16 & 0xFF);
	dg = (color2 >> 8 & 0xFF) - (color1 >> 8 & 0xFF);
	db = (color2 & 0xFF) - (color1 & 0xFF);
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
		put_pixel(img, x, y, color1 + (dr * (x - x1) / dx << 16) + (dg * (x - x1) / dx << 8) + db * (x - x1) / dx);
		if (d > 0)
		{
			y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		x++;
	}
}

void	draw_line_high_gradient(t_img *img, int x1, int y1, int x2, int y2, int color1, int color2)
{
	int	dr;
	int	dg;
	int	db;
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	y;
	int	x;

	dr = (color2 >> 16 & 0xFF) - (color1 >> 16 & 0xFF);
	dg = (color2 >> 8 & 0xFF) - (color1 >> 8 & 0xFF);
	db = (color2 & 0xFF) - (color1 & 0xFF);
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
		put_pixel(img, x, y, color1 + (dr * (y - y1) / dy << 16) + (dg * (y - y1) / dy << 8) + db * (y - y1) / dy);
		if (d > 0)
		{
			x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		y++;
	}
}

void	draw_line_gradient(t_img *img, int x1, int y1, int x2, int y2, int color1, int color2)
{
	int	dx;
	int	dy;

	dx = (x2 - x1 >= 0) ? x2 - x1 : x1 - x2;
	dy = (y2 - y1 >= 0) ? y2 - y1 : y1 - y2;
	if (dy < dx)
	{
		if (x1 > x2)
			draw_line_low_gradient(img, x2, y2, x1, y1, color2, color1);
		else
			draw_line_low_gradient(img, x1, y1, x2, y2, color1, color2);
	}
	else
	{
		if (y1 > y2)
			draw_line_high_gradient(img, x2, y2, x1, y1, color2, color1);
		else
			draw_line_high_gradient(img, x1, y1, x2, y2, color1, color2);
	}
}
