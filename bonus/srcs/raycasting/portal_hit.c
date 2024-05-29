#include "raycasting.h"
#include "tile_address.h"

# include <stdio.h>
# include <math.h>

static int	get_relative_position(int f1, int f2)
{
	// int	diff;
	// int	relative_position;
	static int	relative_positions[4][4] = {
		{0, 1, 2, 3},
		{3, 0, 1, 2},
		{2, 3, 0, 1},
		{1, 2, 3, 0}
	};

	// diff = (f2 - f1) % 4;
	// relative_position = (diff + 4) % 4;
	// return (relative_position);
	return (relative_positions[f1][f2]);
}

static void	apply_rotation(t_player *player, double angle)
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

void	portal_hit(t_cubscene *scene, t_ray *ray, t_player *player)
{
	int	portal_id;
	int	dest_portal_id;
	int	relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

	(void)player;
	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
	portals = scene->portals.tab;
	if (portals[portal_id].is_open == 0)
		return ;	// portal is closed
	dest_portal_id = portals[portal_id].linked_portal;
	diff.x = (portals[portal_id].pos.x + 0.5) - player->pos.x;
	diff.y = (portals[portal_id].pos.y + 0.5) - player->pos.y;
	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
	if (relative_position == 0)	// same face
	{
		// rotate vector (diff) 180 degrees relative to the portal
		// diff.y *= 0.999999999999999;	// to avoid floating point precision errors
		apply_rotation(player, PI);
		player->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		player->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				player->pos.x -= 1;
			else
				player->pos.x += 1;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				player->pos.y -= 1;
			else
				player->pos.y += 1;
		}
	}
	else if (relative_position == 1)	// left face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff = (t_v2d_d){-diff.y, diff.x};
		apply_rotation(player, -PI_2);
		player->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		player->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				player->pos.y -= 1;
			else
				player->pos.y += 1;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				player->pos.x += 1;
			else
				player->pos.x -= 1;
		}
	}
	else if (relative_position == 2)	// opposite face
	{
		// rotate vector (diff) 0 degrees relative to the portal
		diff.x = -diff.x;
		diff.y = -diff.y;
		player->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		player->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				player->pos.x += 1;
			else
				player->pos.x -= 1;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				player->pos.y += 1;
			else
				player->pos.y -= 1;
		}
	}
	else if (relative_position == 3)	// right face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff = (t_v2d_d){diff.y, -diff.x};
		apply_rotation(player, PI_2);
		player->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		player->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				player->pos.y += 1;
			else
				player->pos.y -= 1;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				player->pos.x -= 1;
			else
				player->pos.x += 1;
		}
	}
}
