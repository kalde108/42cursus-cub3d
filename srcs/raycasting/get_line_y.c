#include "cub3d.h"
#include "draw.h"

void	get_line_y(t_vline *line, double perp_wall_dist)
{
	int	line_height;

	if (perp_wall_dist == 0)
		line_height = HEIGHT;
	else
		line_height = (int)(HEIGHT / perp_wall_dist);
	line->start = -line_height / 2 + HEIGHT / 2;
	line->end = line_height / 2 + HEIGHT / 2;
}
