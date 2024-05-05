/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:29:16 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 22:45:13 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"

void	init_tex(t_tex *img)
{
	img->filepath = NULL;
	img->ptr = NULL;
}

void	init_scene(t_cubscene *ptr)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		init_tex(ptr->texture + i++);
	ptr->floor.a = 255;
	ptr->ceilling.a = 255;
	ptr->map = NULL;
}
