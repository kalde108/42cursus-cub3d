/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:29:16 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 02:29:18 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"

void	init_scene(t_cubscene *ptr)
{
	ptr->texture.north = NULL;
	ptr->texture.south = NULL;
	ptr->texture.west = NULL;
	ptr->texture.east = NULL;
	ptr->floor.r = -1;
	ptr->floor.g = -1;
	ptr->floor.b = -1;
	ptr->ceilling.r = -1;
	ptr->ceilling.g = -1;
	ptr->ceilling.b = -1;
}
