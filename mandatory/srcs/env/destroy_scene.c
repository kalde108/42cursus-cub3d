/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:51:21 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "cubscene.h"

static void	destroy_scene_textures(t_cubscene *scene, void *mlx_ptr);

void	destroy_scene(t_cubscene *scene, void *mlx_ptr)
{
	destroy_scene_textures(scene, mlx_ptr);
	free(scene->map);
}

static void	destroy_scene_textures(t_cubscene *scene, void *mlx_ptr)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		free(scene->texture[i].filepath);
		if (scene->texture[i].mlx_img)
		{
			mlx_destroy_image(mlx_ptr, scene->texture[i].mlx_img);
		}
		i++;
	}
}
