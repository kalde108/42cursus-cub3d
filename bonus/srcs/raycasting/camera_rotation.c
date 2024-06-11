/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:58 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:51:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "camera.h"

void	camera_rotation(t_camera *camera, double angle)
{
	double	old_x;

	old_x = camera->dir.x;
	camera->dir.x = camera->dir.x * cos(angle) \
						- camera->dir.y * sin(angle);
	camera->dir.y = old_x * sin(angle) + camera->dir.y * cos(angle);
	old_x = camera->plane.x;
	camera->plane.x = camera->plane.x * cos(angle) \
							- camera->plane.y * sin(angle);
	camera->plane.y = old_x * sin(angle) + \
							camera->plane.y * cos(angle);
}
