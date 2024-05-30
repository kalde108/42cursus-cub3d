#include <math.h>

#include "player.h"

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(angle) \
						- player->dir.y * sin(angle);
	player->dir.y = old_dir_x * sin(angle) + player->dir.y * cos(angle);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(angle) \
							- player->plane.y * sin(angle);
	player->plane.y = old_plane_x * sin(angle) + \
							player->plane.y * cos(angle);
}
