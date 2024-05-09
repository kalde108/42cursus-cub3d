/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:31:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 14:20:33 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"
#include "ft_math.h"

t_tex	get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_tex *textures)
{
	if (scene->map[map_pos.y * scene->width + map_pos.x] == '1')
		return (textures[W1]);
	else if (scene->map[map_pos.y * scene->width + map_pos.x] == '2')
		return (textures[W2]);
	else
		return (textures[W1]);
}
