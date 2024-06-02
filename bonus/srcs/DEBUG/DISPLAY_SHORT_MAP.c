#include "cub3d.h"
#include "tile_address.h"

#include <stdio.h>

void DISPLAY_SHORT_MAP(t_c3_env *env)
{
	int	i;
	int	cell;

	i = 0;
	while (i < env->scene.width * env->scene.height)
	{
		cell = env->scene.map[i];
		if (IS_WALL(cell))
			printf("\e[48;2;255;0;0m  \e[0m");
		else if (IS_PORTAL(cell))
		{
			int id = GET_PORTAL(cell);
			if (env->scene.portals.tab[id].is_open)
				printf("\e[48;2;0;0;255m  \e[0m");
			else
				printf("\e[48;2;255;255;255m  \e[0m");
		}
		else if (IS_FL_CE(cell))
			printf("\e[48;2;0;0;0m  \e[0m");
		else
			printf("  ");
		i++;
		if (i % env->scene.width == 0)
			printf("\n");
	}
}
