#include <unistd.h>
#include <math.h>

#include "cub3d.h"
#include "libft.h"
#include "cubdef.h"
#include "parsing.h"

static int get_portal_opening(t_vector *map, t_v2d_i portal);

int config_portals(t_vector *map, t_cubscene *scene)
{
	int		i;

	i = 0;
	while (i < scene->portals.total)
	{
		scene->portals.tab[i].face = get_portal_opening(map, scene->portals.tab[i].pos);
		ft_dprintf(2, "portal %d at x%d y%d | face %d\n", i, scene->portals.tab[i].pos.x, scene->portals.tab[i].pos.y, scene->portals.tab[i].face);
		i++;
	}
	return (0);
}

static int get_portal_opening(t_vector *map, t_v2d_i portal)
{
	const t_v2d_i	adjacent[] = {
		(t_v2d_i){0, 1},
		(t_v2d_i){-1, 0},
		(t_v2d_i){0, -1},
		(t_v2d_i){1, 0}
	};
	int				i;
	char			*cell;

	i = 0;
	while (i < 4)
	{
		cell = ft_vector_get(ft_vector_get(map, portal.y + adjacent[i].y), portal.x + adjacent[i].x);
		if (cell && '.' == *cell)
			return (i);
		i++;
	}
	return (-1);
}
