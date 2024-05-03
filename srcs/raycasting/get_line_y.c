#include "cub3d.h"

void	get_line_y(int *line_y, double perp_wall_dist)
{
	int	line_height;

	if (perp_wall_dist == 0)
		line_height = HEIGHT;
	else
		line_height = (int)(HEIGHT / perp_wall_dist);
	line_y[0] = -line_height / 2 + HEIGHT / 2;
	if (line_y[0] < 0)
		line_y[0] = 0;
	line_y[1] = line_height / 2 + HEIGHT / 2;
	if (line_y[1] >= HEIGHT)
		line_y[1] = HEIGHT - 1;
}
