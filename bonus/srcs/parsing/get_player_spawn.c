#include <unistd.h>
#include <math.h>

#include "libft.h"
#include "parsing.h"

static int	search_line(t_vector *line, t_player *player, bool *found, int y);
static void	get_player_orientation(char c, t_player *player);

int	get_player_spawn(t_vector *map, t_player *player)
{
	bool		found;
	t_vector	*line;
	size_t		i;

	found = false;
	i = -1;
	while (++i < map->total)
	{
		line = ft_vector_get(map, i);
		if (search_line(line, player, &found, i))
			return (-1);
	}
	if (false == found)
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, NO_PLAYER);
		return (-1);
	}
	return (0);
}

static int	search_line(t_vector *line, t_player *player, bool *found, int y)
{
	char	*cell;
	size_t	i;

	i = -1;
	while (++i < line->total)
	{
		cell = ft_vector_get(line, i);
		if (1 == ft_ischarset(*cell, SPAWN_CHARSET))
		{
			if (true == *found)
			{
				ft_dprintf(STDERR_FILENO, MAP_ERR2, MULTIPLE_PLAYER);
				return (-1);
			}
			*found = true;
			player->camera.pos.x = i + 0.5;
			player->camera.pos.y = y + 0.5;
			get_player_orientation(*cell, player);
			init_timer(&player->interact, INTERACTION_COOLDOWN, AUTO_RESET);
		}
	}
	return (0);
}

static void	get_player_orientation(char c, t_player *player)
{
	const char		charset[] = {'N', 'S', 'E', 'W'};
	const double	x[] = {0, 0, 1, -1};
	const double	y[] = {-1, 1, 0, 0};
	int				i;

	i = 0;
	while (charset[i] != c)
		i++;
	player->camera.dir.x = x[i];
	player->camera.dir.y = y[i];
	player->camera.plane.x = -y[i] * tan(FOV / 2.0 * PI / 180.0);
	player->camera.plane.y = x[i] * tan(FOV / 2.0 * PI / 180.0);
	player->mv_speed = PLAYER_MOVEMENT_SPEED;
	player->rt_speed = PLAYER_ROTATION_SPEED;
}
