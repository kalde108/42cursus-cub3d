/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/10 03:04:12 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "cubscene.h"

static void	destroy_scene_textures(t_tex **texture, void *mlx_ptr);

void	destroy_scene(t_cubscene *scene, void *mlx_ptr)
{
	if (scene->texture)
	{
		destroy_scene_textures(scene->texture, mlx_ptr);
		free(scene->texture);
		scene->texture = NULL;
	}
	free(scene->map);
}

static void	destroy_scene_textures(t_tex **texture, void *mlx_ptr)
{
	int	i;
	int	j;

	i = 0;
	while (i < BASIC_TEXTURE)
	{
		j = 0;
		while (j < MAX_TEXTURE)
		{
			if (NULL != texture[i][j].sprite)
			{
				free(texture[i][j].sprite->filepath);
				if (texture[i][j].sprite->mlx_img)
					mlx_destroy_image(mlx_ptr, texture[i][j].sprite->mlx_img);
				free(texture[i][j].sprite);
			}
			j++;
		}
		free(texture[i++]);
	}
}
