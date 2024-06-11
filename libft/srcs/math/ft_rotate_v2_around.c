/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_v2_around.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:08:16 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 19:08:38 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ft_math.h"

void	ft_rotate_v2_around(t_v2d_d *v, double angle, t_v2d_d center)
{
	double	sin_angle;
	double	cos_angle;
	double	old_x;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	old_x = v->x;
	v->x = (v->x - center.x) * cos_angle - (v->y - center.y) * sin_angle
		+ center.x;
	v->y = (old_x - center.x) * sin_angle + (v->y - center.y) * cos_angle
		+ center.y;
}
