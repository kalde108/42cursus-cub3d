/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:19 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 17:48:18 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "tile_address.h"

// rotate 180 degrees relative to the portal
static void	same_face(t_portal *dest_portal,
						t_camera *camera,
						t_v2d_d diff,
						t_ray *ray)
{
	camera_rotation(camera, PI);
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			camera->pos.x -= 1;
		else
			camera->pos.x += 1;
	}
	else if (ray->side == 1)
	{
		if (ray->ray_dir.y > 0)
			camera->pos.y -= 1;
		else
			camera->pos.y += 1;
	}
}

// rotate 90 degrees relative to the portal
static void	left_face(t_portal *dest_portal,
						t_camera *camera,
						t_v2d_d diff,
						t_ray *ray)
{
	camera_rotation(camera, -PI_2);
	diff = (t_v2d_d){-diff.y, diff.x};
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			camera->pos.y -= 1;
		else
			camera->pos.y += 1;
	}
	else if (ray->side == 1)
	{
		if (ray->ray_dir.y > 0)
			camera->pos.x += 1;
		else
			camera->pos.x -= 1;
	}
}

// rotate 0 degrees relative to the portal
static void	opposite_face(t_portal *dest_portal,
							t_camera *camera,
							t_v2d_d diff,
							t_ray *ray)
{
	diff.x = -diff.x;
	diff.y = -diff.y;
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			camera->pos.x += 1;
		else
			camera->pos.x -= 1;
	}
	else if (ray->side == 1)
	{
		if (ray->ray_dir.y > 0)
			camera->pos.y += 1;
		else
			camera->pos.y -= 1;
	}
}

// rotate 90 degrees relative to the portal
static void	right_face(t_portal *dest_portal,
						t_camera *camera,
						t_v2d_d diff,
						t_ray *ray)
{
	camera_rotation(camera, PI_2);
	diff = (t_v2d_d){diff.y, -diff.x};
	camera->pos.x = dest_portal->pos.x + 0.5 + diff.x;
	camera->pos.y = dest_portal->pos.y + 0.5 + diff.y;
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			camera->pos.y += 1;
		else
			camera->pos.y -= 1;
	}
	else if (ray->side == 1)
	{
		if (ray->ray_dir.y > 0)
			camera->pos.x -= 1;
		else
			camera->pos.x += 1;
	}
}

void	portal_hit(t_cubscene *scene, t_ray *ray, t_camera *camera)
{
	int			portal_id;
	int			dest_portal_id;
	int			relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

	portal_id = (ray->cell & PORTAL_MASK) >> PORTAL_SHIFT;
	portals = scene->portals.tab;
	dest_portal_id = portals[portal_id].linked_portal;
	diff.x = (portals[portal_id].pos.x + 0.5) - camera->pos.x;
	diff.y = (portals[portal_id].pos.y + 0.5) - camera->pos.y;
	relative_position = get_relative_position(portals[portal_id].face,
			portals[dest_portal_id].face);
	if (relative_position == 0)
		same_face(portals + dest_portal_id, camera, diff, ray);
	else if (relative_position == 1)
		left_face(portals + dest_portal_id, camera, diff, ray);
	else if (relative_position == 2)
		opposite_face(portals + dest_portal_id, camera, diff, ray);
	else if (relative_position == 3)
		right_face(portals + dest_portal_id, camera, diff, ray);
}
