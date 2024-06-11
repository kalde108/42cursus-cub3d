/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:08:35 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 19:08:36 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ft_math.h"

void	ft_rotate_v2(t_v2d_d *v, double angle)
{
	double	old_x;

	old_x = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = old_x * sin(angle) + v->y * cos(angle);
}
