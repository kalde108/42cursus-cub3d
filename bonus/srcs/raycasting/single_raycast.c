/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:32 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 18:29:09 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "tile_address.h"

static inline int	not_linked_portal(t_ray *ray, t_portals *portals)
{
	return (ray->cell & TYPE_PORTAL
		&& NO_LINK == portals->tab[(ray->cell & PORTAL_MASK) \
		>> PORTAL_SHIFT].linked_portal);
}

void	single_raycast(t_cubscene *scene,
						t_camera camera,
						t_hit_buffer hit_buf[MAX_LAYERS])
{
	t_ray			ray;
	int				hit_count;
	t_hit_buffer	*buf_ptr;

	hit_count = 0;
	ray = (t_ray){0};
	while (((ray.cell & TYPE_MASK) ^ TYPE_WALL
			&& !not_linked_portal(&ray, &scene->portals))
		&& hit_count < MAX_LAYERS)
	{
		if (ray.cell & TYPE_PORTAL)
			portal_hit(scene, &ray, &camera);
		ray_calculation(&camera, &ray);
		ft_dda(scene, &ray);
		buf_ptr = hit_buf + hit_count;
		buf_ptr->side = ray.side;
		buf_ptr->cell = ray.cell;
		buf_ptr->z = ray.perp_wall_dist;
		buf_ptr->texture = get_wall_texture(scene, ray.cell, scene->elems);
		buf_ptr->tex_x = get_tex_x(&ray, buf_ptr->texture->width, &camera);
		get_line_y(hit_buf, ray.perp_wall_dist);
		buf_ptr->camera = camera;
		hit_count++;
	}
	hit_buf->count = hit_count;
}
