/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/02 18:21:25 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "libft.h"
#include "tile_address.h"

# include <math.h>
# include <stdio.h>

// static int	get_relative_position(int f1, int f2)
// {
// 	int	diff;
// 	int	relative_position;

// 	diff = (f2 - f1) % 4;
// 	relative_position = (diff + 4) % 4;
// 	return (relative_position);
// }

// static void	delta_dist_init(t_ray *ray)
// {
// 	if (ray->ray_dir.x == 0)
// 		ray->delta_dist.x = 1e30;
// 	else
// 		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
// 	if (ray->ray_dir.y == 0)
// 		ray->delta_dist.y = 1e30;
// 	else
// 		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
// }

// static void	step_init(t_v2d_d *pos, t_ray *ray)
// {
// 	if (ray->ray_dir.x < 0)
// 	{
// 		ray->step.x = -1;
// 		ray->side_dist.x = (pos->x - ray->map_pos.x) \
// 							* ray->delta_dist.x;
// 	}
// 	else
// 	{
// 		ray->step.x = 1;
// 		ray->side_dist.x = (ray->map_pos.x + 1.0 - pos->x) \
// 							* ray->delta_dist.x;
// 	}
// 	if (ray->ray_dir.y < 0)
// 	{
// 		ray->step.y = -1;
// 		ray->side_dist.y = (pos->y - ray->map_pos.y) \
// 							* ray->delta_dist.y;
// 	}
// 	else
// 	{
// 		ray->step.y = 1;
// 		ray->side_dist.y = (ray->map_pos.y + 1.0 - pos->y) \
// 							* ray->delta_dist.y;
// 	}
// }

// static void	portal_hit(t_cubscene *scene, t_ray *ray, t_camera *camera)
// {
// 	int	portal_id;
// 	int	dest_portal_id;
// 	int	relative_position;
// 	t_portal	*portals;
// 	double	tmp1;
// 	// int	tmp2;
// 	t_v2d_d	tmp3;

// 	(void)camera;
// 	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
// 	portals = scene->portals.tab;
// 	if (portals[portal_id].is_open == 0)
// 		return ;	// portal is closed
// 	dest_portal_id = portals[portal_id].linked_portal;
// 	ray->map_pos = scene->portals.tab[dest_portal_id].pos;
// 	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
// 	if (relative_position == 0)	// same face
// 	{
// 		if (ray->side == 0)
// 		{
// 			ray->step.x = -ray->step.x;
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.x -= 1;
// 			else
// 				ray->map_pos.x += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			ray->step.y = -ray->step.y;
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.y -= 1;
// 			else
// 				ray->map_pos.y += 1;
// 		}
// 	}
// 	else if (relative_position == 1)	// left face
// 	{
// 		// tmp1 = ray->step.x;
// 		// ray->step.x = ray->step.y;
// 		// ray->step.y = -tmp1;
// 		// ray->total_perp_wall_dist = ray->perp_wall_dist;	// debug
// 			// tmp1 = ray->ray_dir.x;
// 			// ray->ray_dir.x = ray->ray_dir.y;
// 			// ray->ray_dir.y = -tmp1;
// 			// delta_dist_init(ray);
// 		// tmp1 = ray->delta_dist.x;
// 		// ray->delta_dist.x = ray->delta_dist.y;
// 		// ray->delta_dist.y = -tmp1;
// 		// tmp1 = ray->side_dist.x;
// 		// ray->side_dist.x = ray->side_dist.y;
// 		// ray->side_dist.y = -tmp1;
// 		// ray->map_pos.x -= 1;
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.y -= 1;
// 			else
// 				ray->map_pos.y += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 		}
// 		// tmp3.x = ray->map_pos.x + ((camera->pos.x - floor(camera->pos.x)));
// 		// tmp3.y = ray->map_pos.y + ( (camera->pos.y - floor(camera->pos.y)));
// 		// step_init(&tmp3, ray);
// 		(void)tmp1;
// 		(void)tmp3;
// 		(void)camera;
// 		// ray->turn = 1;
// 	}
// 	else if (relative_position == 2)	// opposite face
// 	{
// 		// vector stays the same
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.y += 1;
// 			else
// 				ray->map_pos.y -= 1;
// 		}
// 	}
// 	else if (relative_position == 3)	// right face
// 	{
// 		// tmp1 = ray->step.x;
// 		// ray->step.x = -ray->step.y;
// 		// ray->step.y = tmp1;
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.y += 1;
// 			else
// 				ray->map_pos.y -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.x -= 1;
// 			else
// 				ray->map_pos.x += 1;
// 		}
// 	}

// 	// if (ray->side == 0)
// 	// {
// 	// 	if (ray->ray_dir.x > 0)
// 	// 		ray->map_pos.x += 1;
// 	// 	else
// 	// 		ray->map_pos.x -= 1;
// 	// }
// 	// else if (ray->side == 1)
// 	// {
// 	// 	if (ray->ray_dir.y > 0)
// 	// 		ray->map_pos.y += 1;
// 	// 	else
// 	// 		ray->map_pos.y -= 1;
// 	// }
// }

# include "cub3d.h"

void	ft_dda(t_cubscene *scene, t_ray *ray, t_camera *camera)	// camera for debug
{
	int	hit;
	int	hit_enable;

	(void)camera; // debug
	hit_enable = 1;
	hit = 0;
	while (hit == 0)
	{
		if ((ray->map_pos.x < 0 && ray->step.x <= 0)
			|| (ray->map_pos.y < 0 && ray->step.y <= 0)
			|| (ray->map_pos.x >= scene->width && ray->step.x >= 0)
			|| (ray->map_pos.y >= scene->height && ray->step.y >= 0))
		{
			// dprintf(2, "%d ALED\n", g_debug);
			// dprintf(2, "%d map_pos out of bounds\tx: %d\ty: %d\n", g_debug, ray->map_pos.x, ray->map_pos.y);
			// dprintf(2, "camera pos\tx: %f\ty: %f\n", camera->pos.x, camera->pos.y);
			// dprintf(2, "camera dir\tx: %f\ty: %f\n", camera->dir.x, camera->dir.y);
			// dprintf(2, "camera plane\tx: %f\ty: %f\n", camera->plane.x, camera->plane.y);
			// dprintf(2, "ray dir\tx: %f\ty: %f\n", ray->ray_dir.x, ray->ray_dir.y);
			// dprintf(2, "ray map_pos\tx: %d\ty: %d\n", ray->map_pos.x, ray->map_pos.y);
		}
		if ((ray->map_pos.x < 0 && ray->step.x > 0)
			|| (ray->map_pos.y < 0 && ray->step.y > 0)
			|| (ray->map_pos.x >= scene->width && ray->step.x < 0)
			|| (ray->map_pos.y >= scene->height && ray->step.y < 0))
		{
			// dprintf(2, "controlled EVA\n");
			hit_enable = 0;
		}
		else
			hit_enable = 1;
		if (hit_enable && IS_WALL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			if (!IS_PORTAL(ray->hit_type))
			{
				hit = 1;
				ray->hit_type = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
			}
		}
		if (hit_enable && IS_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			if (IS_PORTAL(ray->hit_type))
				ray->hit_type = 0;
			else
			{
				hit = 1;
				ray->hit_type = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
			}
		}
		if (!hit)
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
		}
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x + ray->total_perp_wall_dist;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y + ray->total_perp_wall_dist;
}
/*

x horizontal

y vertical


	    1
	_________
	|		|
0	|		| 2
	|		|
	---------
	    3


0 -> 0	(same face)
v.x = -v.x
v.y = v.y

0 -> 1	(left face)
v.x = v.y
v.y = -v.x

0 -> 2	(opposite face)
v.x = v.x
v.y = v.y

0 -> 3	(right face)
v.x = -v.y
v.y = v.x

1 -> 0	(right face)
v.x = -v.y
v.y = v.x

1 -> 1	(same face)
v.x = v.x
v.y = -v.y

1 -> 2	(left face)
v.x = v.y
v.y = -v.x

1 -> 3	(opposite face)
v.x = v.x
v.y = v.y

2 -> 0	(opposite face)
v.x = v.x
v.y = v.y

2 -> 1	(right face)
v.x = -v.y
v.y = v.x

2 -> 2	(same face)
v.x = -v.x
v.y = v.y

2 -> 3	(left face)
v.x = v.y
v.y = -v.x

3 -> 0	(left face)
v.x = v.y
v.y = -v.x

3 -> 1	(opposite face)
v.x = v.x
v.y = v.y

3 -> 2	(right face)
v.x = -v.y
v.y = v.x

3 -> 3	(same face)
v.x = v.x
v.y = -v.y

same face :
	reverse sign based on the side of the wall hit
	if vertical wall, reverse x
	if horizontal wall, reverse y

left face :
	x = y
	y = -x

opposite face :
	vector stays the same

right face :
	x = -y
	y = x


int get_relative_position(int f1, int f2)
{
	int	diff;
	int	relative_position;

	diff = (f2 - f1) % 4;
	relative_position = (diff + 4) % 4;
	return (relative_position);
}

get_relative_position(0, 0) = 0
get_relative_position(0, 1) = 1
get_relative_position(0, 2) = 2
get_relative_position(0, 3) = 3
get_relative_position(1, 0) = 3
get_relative_position(1, 1) = 0
get_relative_position(1, 2) = 1
get_relative_position(1, 3) = 2
get_relative_position(2, 0) = 2
get_relative_position(2, 1) = 3
get_relative_position(2, 2) = 0
get_relative_position(2, 3) = 1
get_relative_position(3, 0) = 1
get_relative_position(3, 1) = 2
get_relative_position(3, 2) = 3
get_relative_position(3, 3) = 0


int	relation = get_relative_position(f1, f2);
if (relation == 0)
{
	// same face
}
else if (relation == 1)
{
	// left face
}
else if (relation == 2)
{
	// opposite face
}
else if (relation == 3)
{
	// right face
}





*/
