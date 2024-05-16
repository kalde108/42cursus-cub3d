/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/13 23:06:19 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "ft_math.h"
#include "tile_address.h"

t_texdata	*get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_tex **textures)
{
	t_tex *texture_block;

	texture_block = &textures[WALL][GET_WALL(scene->map[map_pos.y * scene->width + map_pos.x])];
	return (texture_block->current);
}
