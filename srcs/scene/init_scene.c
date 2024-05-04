/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:29:16 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 02:53:54 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"

void	init_img(t_img *img)
{
	img->filepath = NULL;
	img->ptr = NULL;
}

void	init_scene(t_cubscene *ptr)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		init_img(ptr->texture + i++);
	ptr->floor.a = 255;
	ptr->ceilling.a = 255;
}
