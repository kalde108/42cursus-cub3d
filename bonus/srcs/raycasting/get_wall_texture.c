/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/11 17:45:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "tile_address.h"

t_texdata	*get_wall_texture(t_cubscene *scene, int cell, t_elem **textures)
{
	if (cell & TYPE_WALL)
		return (textures[WALL][cell & WALL_MASK].current);
	else if (cell & TYPE_PORTAL
		&& scene->portals.tab[(cell & PORTAL_MASK) >> PORTAL_SHIFT].is_open)
		return (textures[PORTAL]->current);
	else if (cell & TYPE_PORTAL)
		return (textures[PORTAL]->frames);
	return (NULL);
}
