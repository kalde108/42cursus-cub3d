/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/06 03:31:15 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "cubscene.h"

t_tex	get_wall_texture(int side, t_v2d_d ray_dir, t_tex *textures)
{
	if (0 == side)
	{
		if (ray_dir.x > 0)
			return (textures[WE]);
		else
			return (textures[EA]);
	}
	else
	{
		if (ray_dir.y > 0)
			return (textures[NO]);
		else
			return (textures[SO]);
	}
}
