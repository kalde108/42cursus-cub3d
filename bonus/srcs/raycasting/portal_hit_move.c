#include "raycasting.h"
#include "tile_address.h"

// rotate 180 degrees relative to the portal
static double	same_face(t_portal *dest_portal,
							t_camera *camera,
							t_v2d_d diff,
							int side)
{
	camera_rotation(camera, PI);
	if (side == 0)
		diff = (t_v2d_d){-diff.x, diff.y};
	else if (side == 1)
		diff = (t_v2d_d){diff.x, -diff.y};
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	return (PI);
}

// rotate 90 degrees relative to the portal
static double	left_face(t_portal *dest_portal,
							t_camera *camera,
							t_v2d_d diff,
							int side)
{
	camera_rotation(camera, -PI_2);
	if (side == 0)
		diff = (t_v2d_d){-diff.y, -diff.x};
	else if (side == 1)
		diff = (t_v2d_d){diff.y, diff.x};
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	return (-PI_2);
}

// rotate 0 degrees relative to the portal
static double	opposite_face(t_portal *dest_portal,
								t_camera *camera,
								t_v2d_d diff,
								int side)
{
	if (side == 0)
		diff = (t_v2d_d){diff.x, -diff.y};
	else if (side == 1)
		diff = (t_v2d_d){-diff.x, diff.y};
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	return (0);
}

// rotate 90 degrees relative to the portal
static double	right_face(t_portal *dest_portal,
							t_camera *camera,
							t_v2d_d diff,
							int side)
{
	camera_rotation(camera, PI_2);
	if (side == 0)
		diff = (t_v2d_d){diff.y, diff.x};
	else if (side == 1)
		diff = (t_v2d_d){-diff.y, -diff.x};
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	return (PI_2);
}

void	portal_hit_move(t_cubscene *scene,
						t_ray *ray,
						t_camera *camera,
						double *rot)
{
	int			portal_id;
	int			dest_portal_id;
	int			relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

	portal_id = GET_PORTAL(ray->cell);
	portals = scene->portals.tab;
	dest_portal_id = portals[portal_id].linked_portal;
	diff.x = (portals[portal_id].pos.x + 0.5) - camera->pos.x;
	diff.y = (portals[portal_id].pos.y + 0.5) - camera->pos.y;
	relative_position = get_relative_position(portals[portal_id].face,
			portals[portal_id].face);
	if (relative_position == 0)
		*rot = same_face(portals + dest_portal_id, camera, diff, ray->side);
	else if (relative_position == 1)
		*rot = left_face(portals + dest_portal_id, camera, diff, ray->side);
	else if (relative_position == 2)
		*rot = opposite_face(portals + dest_portal_id, camera, diff, ray->side);
	else if (relative_position == 3)
		*rot = right_face(portals + dest_portal_id, camera, diff, ray->side);
}
