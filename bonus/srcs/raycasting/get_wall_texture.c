/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/05 15:09:50 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "tile_address.h"

t_texdata	*get_wall_texture(t_cubscene *scene, int cell, t_elem **textures)
{
	if (IS_WALL(cell))
		return (textures[WALL][GET_WALL(cell)].current);
	else if (IS_PORTAL(cell) && scene->portals.tab[GET_PORTAL(cell)].is_open)
		return (textures[PORTAL]->current);
	else if (IS_PORTAL(cell))
		return (textures[PORTAL]->frames);
	return (NULL);
}
