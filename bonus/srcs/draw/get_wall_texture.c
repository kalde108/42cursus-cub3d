/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/20 21:18:12 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "ft_math.h"
#include "tile_address.h"

# include <stdio.h>

t_texdata	*get_wall_texture(t_cubscene *scene, int cell, t_elem **textures)
{
	t_elem	*texture_block;

	(void)scene;
	if (IS_WALL(cell))
		texture_block = &textures[WALL][GET_WALL(cell)];
	else if (IS_PORTAL(cell))
		texture_block = textures[PORTAL];
	else
	{
		dprintf(2, "Error\n");
		// dprintf(2, "Invalid cell type: %d\tat x = %d, y = %d\n", cell, map_pos.x, map_pos.y);
		return (NULL);
	}
	return (texture_block->current);
}
