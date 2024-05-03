/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:29:16 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 15:38:29 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"

void	init_scene(t_cubscene *ptr)
{
	ptr->texture.north = NULL;
	ptr->texture.south = NULL;
	ptr->texture.west = NULL;
	ptr->texture.east = NULL;
	ptr->floor.a = 255;
	ptr->ceilling.a = 255;
	ptr->map = (t_vector){0};
}
