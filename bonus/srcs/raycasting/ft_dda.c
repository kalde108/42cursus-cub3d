/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/20 17:51:27 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "libft.h"
#include "tile_address.h"

# include <math.h>

static void	portal_hit(t_cubscene *scene, t_ray *ray)
{
	int	portal_id;
	int	dest_portal_id;
	// t_v2d_i	diff;

	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
	dest_portal_id = scene->portals.tab[portal_id].linked_portal;
	if (dest_portal_id != -1)
	{
		// diff.x = scene->portals.tab[dest_portal_id].pos.x - scene->portals.tab[portal_id].pos.x;
		// diff.y = scene->portals.tab[dest_portal_id].pos.y - scene->portals.tab[portal_id].pos.y;
		ray->map_pos = scene->portals.tab[dest_portal_id].pos;
		// ray->side_dist.x -= diff.x;
		// ray->side_dist.y -= diff.y;
	}
}

void	ft_dda(t_cubscene *scene, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (IS_WALL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			hit = 1;
			ray->hit_type = GET_TYPE(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
		}
		if (IS_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			portal_hit(scene, ray);
			hit = 1;
			ray->hit_type = GET_TYPE(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
		}
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}
