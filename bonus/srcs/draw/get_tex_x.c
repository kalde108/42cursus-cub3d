/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:40:32 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/29 15:09:39 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "raycasting.h"

int	get_tex_x(t_ray *ray, int width, t_camera *camera)
{
	double	wall_x;

	if (0 == ray->side)
		wall_x = camera->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wall_x = camera->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	wall_x -= floor(wall_x);
	if ((0 == ray->side && ray->ray_dir.x < 0)
		|| (1 == ray->side && ray->ray_dir.y > 0))
		wall_x = 1.0 - wall_x;
	return (wall_x * width);
}
