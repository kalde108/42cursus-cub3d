/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 18:20:09 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "ft_math.h"
#include "tile_address.h"

t_texdata	*get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_tex **textures)
{
	t_tex *texture_block;

	texture_block = &textures[WALL][GET_WALL(scene->map[map_pos.y * scene->width + map_pos.x])];
	if (texture_block->n == 1)
		return (texture_block->sprite);
	return (NULL);
}
