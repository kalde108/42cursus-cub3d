/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 19:00:29 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "cubscene.h"

static void	destroy_scene_textures(t_elem **texture, void *mlx_ptr);

void	destroy_scene(t_cubscene *scene, void *mlx_ptr)
{
	if (scene->elems)
	{
		destroy_scene_textures(scene->elems, mlx_ptr);
		free(scene->elems);
		scene->elems = NULL;
	}
	free(scene->map);
}

static void	destroy_scene_textures(t_elem **texture, void *mlx_ptr)
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
