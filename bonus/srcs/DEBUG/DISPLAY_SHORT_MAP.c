#include "cub3d.h"
#include "tile_address.h"

#include <stdio.h>

void DISPLAY_SHORT_MAP(t_c3_env *env)
{
	int		i;
	int	s;

	i = 0;
	while (i < env->scene.width * env->scene.height)
	{
		s = env->scene.map[i];
		if (IS_WALL(s))
			printf("WW");
		else if (IS_PORTAL(s))
			printf("PP");
		else if (IS_FL_CE(s))
			printf("..");
		else
			printf("  ");
		i++;
		if (i % env->scene.width == 0)
			printf("\n");
	}
}
