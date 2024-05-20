/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/20 15:03:46 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "ft_math.h"
#include "tile_address.h"

# include <stdio.h>

t_texdata	*get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_elem **textures)
{
	t_elem *texture_block;
	short	cell;

	cell = scene->map[map_pos.y * scene->width + map_pos.x];
	if (IS_WALL(cell))
		texture_block = &textures[WALL][GET_ID(cell)];
	else if (IS_PORTAL(cell))
		texture_block = textures[PORTAL];
	else
		return (NULL);
	return (texture_block->current);
}
