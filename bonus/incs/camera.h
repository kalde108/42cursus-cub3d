/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:59:18 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:59:19 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ft_math.h"

typedef struct s_camera
{
	t_v2d_d	pos;
	t_v2d_d	dir;
	t_v2d_d	plane;
}	t_camera;

#endif