/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/12 18:14:20 by ibertran         ###   ########lyon.fr   */
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
	int	k;

	i = 0;
	while (i < BASIC_TEXTURE)
	{
		j = 0;
		while (j < MAX_TEXTURE)
		{
			k = 0;
			while (k < texture[i][j].n)
			{
				free(texture[i][j].frames[k].filepath);
				if (texture[i][j].frames[k].mlx_img)
					mlx_destroy_image(mlx_ptr, texture[i][j].frames[k].mlx_img);
				k++;
			}
			free(texture[i][j].frames);
			j++;
		}
		free(texture[i++]);
	}
}
