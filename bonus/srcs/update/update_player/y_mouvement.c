/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_mouvement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:41 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 18:14:51 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "update.h"
#include "tile_address.h"

static int	change_y(t_ray *ray,
						t_portals *portals,
						t_camera *camera,
						t_v2d_d *move_vec)
{
	double	offset;

	if (ray->cell & TYPE_PORTAL
		&& NO_LINK != portals->tab[(ray->cell & PORTAL_MASK) \
		>> PORTAL_SHIFT].linked_portal)
		offset = PORTAL_OFFSET;
	else
		offset = PLAYER_SIZE;
	if (ray->perp_wall_dist > fabs(move_vec->y) + offset)
	{
		camera->pos.x += move_vec->x;
		camera->pos.y += move_vec->y;
		return (1);
	}
	else if (ray->perp_wall_dist > offset)
	{
		camera->pos.x += (ray->perp_wall_dist - offset) * camera->dir.x;
		camera->pos.y += (ray->perp_wall_dist - offset) * camera->dir.y;
		move_vec->x -= (ray->perp_wall_dist - offset) * camera->dir.x;
		move_vec->y -= (ray->perp_wall_dist - offset) * camera->dir.y;
	}
	return (0);
}

void	y_mouvement(t_cubscene *scene, t_player *player, t_v2d_d move_vec)
{
	t_ray		ray;
	t_camera	camera;
	double		rot;

	rot = 0;
	camera.pos = player->camera.pos;
	camera.dir = (t_v2d_d){0, (move_vec.y > 0) - (move_vec.y < 0)};
	ray = (t_ray){0};
	while ((ray.cell & TYPE_MASK) ^ TYPE_WALL && !(ray.cell & TYPE_PORTAL \
		&& NO_LINK == scene->portals.tab[(ray.cell & PORTAL_MASK) \
		>> PORTAL_SHIFT].linked_portal))
	{
		if (ray.cell & TYPE_PORTAL)
		{
			portal_hit_move(scene, &ray, &camera, &rot);
			rotate_player(player, rot);
			ft_rotate_v2(&move_vec, rot);
		}
		ray_calculation(&camera, &ray);
		ray.cell = 0;
		ft_dda(scene, &ray);
		if (change_y(&ray, &scene->portals, &camera, &move_vec))
			break ;
	}
	player->camera.pos = camera.pos;
}
