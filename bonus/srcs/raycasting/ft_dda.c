/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/05 14:12:17 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "tile_address.h"

static int	get_hit(t_cubscene *scene, t_ray *ray, size_t pos)
{
	if (IS_WALL(scene->map[pos])
		&& !IS_PORTAL(ray->cell))
	{
		ray->cell = scene->map[pos];
		return (1);
	}
	if (IS_PORTAL(scene->map[pos]))
	{
		if (!IS_PORTAL(ray->cell))
		{
			ray->cell = scene->map[pos];
			return (1);
		}
		if (scene->portals.tab[GET_PORTAL(ray->cell)].linked_portal
			== GET_PORTAL(scene->map[pos]))
			ray->cell = 0;
	}
	return (0);
}

static void	move_ray(t_ray *ray)
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

void	ft_dda(t_cubscene *scene, t_ray *ray)
{
	int	hit;
	int	hit_enable;

	hit_enable = 1;
	hit = 0;
	while (hit == 0)
	{
		hit_enable = !((ray->map_pos.x < 0 && ray->step.x > 0)
				|| (ray->map_pos.y < 0 && ray->step.y > 0)
				|| (ray->map_pos.x >= scene->width && ray->step.x < 0)
				|| (ray->map_pos.y >= scene->height && ray->step.y < 0));
		if (hit_enable)
			hit = get_hit(scene,
					ray,
					ray->map_pos.y * scene->width + ray->map_pos.x);
		if (!hit)
			move_ray(ray);
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
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

/*

void	ft_dda(t_cubscene *scene, t_ray *ray)
{
	int	hit;
	int	hit_enable;

	hit_enable = 1;
	hit = 0;
	while (hit == 0)
	{
		if ((ray->map_pos.x < 0 && ray->step.x <= 0)
			|| (ray->map_pos.y < 0 && ray->step.y <= 0)
			|| (ray->map_pos.x >= scene->width && ray->step.x >= 0)
			|| (ray->map_pos.y >= scene->height && ray->step.y >= 0))
		{
			dprintf(2, "%d ALED\n", g_debug);
			// dprintf(2, "hit_enable = %d\n", hit_enable);
			// dprintf(2, "\t%d map_pos out of bounds\tx: %d\ty: %d\n", g_debug, ray->map_pos.x, ray->map_pos.y);
			// dprintf(2, "\t%d map_pos out of bounds", g_debug);
			// dprintf(2, "\tcamera pos\tx: %f\ty: %f\n", camera->pos.x, camera->pos.y);
			// dprintf(2, "\tcamera dir\tx: %f\ty: %f\n", camera->dir.x, camera->dir.y);
			// dprintf(2, "camera plane\tx: %f\ty: %f\n", camera->plane.x, camera->plane.y);
			// dprintf(2, "\tray dir\tx: %f\ty: %f\n", ray->ray_dir.x, ray->ray_dir.y);
			// dprintf(2, "\tray map_pos\tx: %d\ty: %d\n", ray->map_pos.x, ray->map_pos.y);
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
			if (!IS_PORTAL(ray->cell))
			{
				hit = 1;
				ray->cell = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
			}
		}
		if (hit_enable && IS_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			if (IS_PORTAL(ray->cell))
			{
				if (scene->portals.tab[GET_PORTAL(ray->cell)].linked_portal == GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
					ray->cell = 0;
			}
			else
			{
				hit = 1;
				ray->cell = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
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
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

*/