#include <unistd.h>
#include <math.h>

#include "cub3d.h"
#include "libft.h"
#include "cubdef.h"
#include "parsing.h"

# include <stdio.h>

static int	search_line(t_vector *line, t_portal *portals, int *count, int y);

int	get_portals(t_vector *map, t_cubscene *scene)
{
	int			count;
	t_vector	*line;
	size_t		i;

	count = 0;
	i = -1;
	while (++i < map->total)
	{
		line = ft_vector_get(map, i);
		if (search_line(line, scene->portals.tab, &count, i))
			return (-1);
	}
	scene->portals.total = count;
	if (count > MAX_PORTALS)
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, TOO_MANY_PORTALS);
		return (-1);
	}
	return (0);
}

static int	search_line(t_vector *line, t_portal *portals, int *count, int y)
{
	char	*cell;
	size_t	i;

	i = -1;
	while (++i < line->total)
	{
		cell = ft_vector_get(line, i);
		if (1 == ft_ischarset(*cell, PORTAL_CHARSET))
		{
			(portals + *count)->id = *count;
			(portals + *count)->pos.x = i;
			(portals + *count)->pos.y = y;
			dprintf(2, "portal %d at %zu %d\n", *count, i, y);
			(*count)++;
		}
	}
	return (0);
}
