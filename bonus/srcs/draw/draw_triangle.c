#include "cub3d.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

# include <math.h>
# include <stdio.h>

static void	swap_vertex(t_vertex *v1, t_vertex *v2)
{
	t_vertex	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

static void	order_vertex(t_triangle *triangle)
{
	if (triangle->v1.y > triangle->v2.y)
		swap_vertex(&triangle->v1, &triangle->v2);
	if (triangle->v1.y > triangle->v3.y)
		swap_vertex(&triangle->v1, &triangle->v3);
	if (triangle->v2.y > triangle->v3.y)
		swap_vertex(&triangle->v2, &triangle->v3);
}

void	draw_triangle_flat_bottom(t_img *img,
			t_triangle triangle,
			t_color color)
{
	double	slope1;
	double	slope2;
	double	x1;
	double	x2;
	int		y;

	slope1 = (triangle.v2.x - triangle.v1.x) / (triangle.v2.y - triangle.v1.y);
	slope2 = (triangle.v3.x - triangle.v1.x) / (triangle.v3.y - triangle.v1.y);
	x1 = triangle.v1.x;
	x2 = triangle.v1.x;
	y = triangle.v1.y;
	while (y <= triangle.v2.y)
	{
		draw_line(img, x1, y, x2, y, color);
		x1 += slope1;
		x2 += slope2;
		y++;
	}
}

void	draw_triangle_flat_top(t_img *img,
			t_triangle triangle,
			t_color color)
{
	double	slope1;
	double	slope2;
	double	x1;
	double	x2;
	int		y;

	slope1 = (triangle.v3.x - triangle.v1.x) / (triangle.v3.y - triangle.v1.y);
	slope2 = (triangle.v3.x - triangle.v2.x) / (triangle.v3.y - triangle.v2.y);
	x1 = triangle.v3.x;
	x2 = triangle.v3.x;
	y = triangle.v3.y;
	while (y > triangle.v1.y)
	{
		draw_line(img, x1, y, x2, y, color);
		x1 -= slope1;
		x2 -= slope2;
		y--;
	}
}

void	draw_triangle(t_img *img, t_triangle triangle, t_color color)
{
	t_vertex	d;

	if (triangle.v1.y == triangle.v2.y && triangle.v1.y == triangle.v3.y)
		return ;
	order_vertex(&triangle);
	if (triangle.v2.y == triangle.v3.y)
		draw_triangle_flat_bottom(img, triangle, color);
	else if (triangle.v1.y == triangle.v2.y)
		draw_triangle_flat_top(img, triangle, color);
	else
	{
		d.x = triangle.v1.x + (triangle.v2.y - triangle.v1.y)
			/ (triangle.v3.y - triangle.v1.y) * (triangle.v3.x - triangle.v1.x);
		d.y = triangle.v2.y;
		draw_triangle_flat_bottom(img,
			(t_triangle){triangle.v1, triangle.v2, d},
			color);
		draw_triangle_flat_top(img,
			(t_triangle){triangle.v2, d, triangle.v3},
			color);
	}
	draw_line(img, triangle.v1.x, triangle.v1.y, triangle.v2.x , triangle.v2.y, color);
	draw_line(img, triangle.v2.x, triangle.v2.y, triangle.v3.x , triangle.v3.y, color);
	draw_line(img, triangle.v3.x, triangle.v3.y, triangle.v1.x , triangle.v1.y, color);
}
