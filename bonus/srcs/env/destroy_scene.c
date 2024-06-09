/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/09 17:27:24 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "cubscene.h"

static void	destroy_basic_textures(t_elem **texture, void *mlx_ptr);
static void	destroy_special_textures(t_elem **elems, void *mlx_ptr);

void	destroy_scene(t_cubscene *scene, void *mlx_ptr)
{
	if (scene->elems)
	{
		destroy_basic_textures(scene->elems, mlx_ptr);
		destroy_special_textures(scene->elems + BASIC_TEXTURE, mlx_ptr);
		free(scene->elems);
		scene->elems = NULL;
	}
	free(scene->map);
}

static void	destroy_basic_textures(t_elem **texture, void *mlx_ptr)
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

static void	destroy_special_textures(t_elem **elems, void *mlx_ptr)
{
	int	i;
	int	j;

	i = 0;
	while (i < SPECIAL_TEXTURES)
	{
		j = 0;
		while (j < elems[i]->n)
		{
			free(elems[i]->frames[j].filepath);
			if (elems[i]->frames[j].mlx_img)
				mlx_destroy_image(mlx_ptr, elems[i]->frames[j].mlx_img);
			j++;
		}
		free(elems[i]->frames);
		free(elems[i]);
		i++;
	}
}
