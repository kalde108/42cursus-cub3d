/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:34 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/29 19:27:23 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubdef.h"
#include "raycasting.h"

#include <math.h>

static void	delta_dist_init(t_ray *ray)
{
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
}

static void	step_init(t_camera *camera, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (camera->pos.x - ray->map_pos.x) \
							* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - camera->pos.x) \
							* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (camera->pos.y - ray->map_pos.y) \
							* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - camera->pos.y) \
							* ray->delta_dist.y;
	}
}

void	screen_ray_calculation(t_camera *camera, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = (2 * x / (double)WIDTH - 1);
	ray->ray_dir.x = camera->dir.x + camera->plane.x * camera_x;
	ray->ray_dir.y = camera->dir.y + camera->plane.y * camera_x;
	delta_dist_init(ray);
	ray->map_pos.x = (int)camera->pos.x;
	ray->map_pos.y = (int)camera->pos.y;
	step_init(camera, ray);
	// ray->hit_type = 0;
	ray->turn = 0;
	// ray->total_perp_wall_dist = 0;
}

void	ray_calculation(t_camera *camera, t_ray *ray)
{
	ray->ray_dir.x = camera->dir.x;
	ray->ray_dir.y = camera->dir.y;
	delta_dist_init(ray);
	ray->map_pos.x = (int)camera->pos.x;
	ray->map_pos.y = (int)camera->pos.y;
	step_init(camera, ray);
	// ray->hit_type = 0;
	ray->turn = 0;
	// ray->total_perp_wall_dist = 0;
}
