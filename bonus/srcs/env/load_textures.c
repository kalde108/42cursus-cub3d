/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:20:25 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 18:20:19 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "mlx.h"
#include "parsing.h"

static int	convert_xmp(void *mlx_ptr, t_texdata *data);

int	load_textures(void *mlx_ptr, t_tex **textures)
{
	int	i;
	int	j;

	i = 0;
	while (i < BASIC_TEXTURE)
	{
		j = 0;
		while (j < MAX_TEXTURE)
		{
			if (NULL != textures[i][j].sprite
				&& convert_xmp(mlx_ptr, textures[i][j].sprite))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	convert_xmp(void *mlx_ptr, t_texdata *data)
{
	data->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			data->filepath,
			&data->width,
			&data->height);
	if (NULL == data->mlx_img)
		return (1);
	free(data->filepath);
	data->filepath = NULL;
	data->addr = mlx_get_data_addr(data->mlx_img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	if (NULL == data->addr)
		return (1);
	return (0);
}
