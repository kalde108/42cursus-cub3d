#include "cub3d.h"
#include "tile_address.h"

t_color	get_tile_color(t_c3_env *env, int cell)
{
	t_color	color;

	if (IS_WALL(cell))
		color = env->scene.elems[WALL][GET_WALL(cell)].current->average_color;
	else if (IS_PORTAL(cell))
	{
		if (env->scene.portals.tab[GET_PORTAL(cell)].is_open)
			color = env->scene.elems[PORTAL]->current->average_color;
		else
			color = env->scene.elems[PORTAL]->frames->average_color;
	}
	else if (IS_FL_CE(cell))
		color = env->scene.elems[FLOOR][GET_FLOOR(cell)].current->average_color;
	else
		color.argb = 0x7F000000;
	return (color);
}
