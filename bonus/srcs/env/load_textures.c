/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:20:25 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 20:17:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "mlx.h"
#include "parsing.h"
#include "cubdef.h"

static int	convert_xmp(void *mlx_ptr, t_texdata *data);

int	load_textures(void *mlx_ptr, t_elem **textures)
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
			while (k < textures[i][j].n)
			{
				if (convert_xmp(mlx_ptr, textures[i][j].frames + k))
					return (-1);
				textures[i][j].current = textures[i][j].frames;
				textures[i][j].dir = 1;
				textures[i][j].options = 1;
				k++;
			}
			j++;
		}
		i++;
	}
	if (convert_xmp(mlx_ptr, textures[PORTAL]->frames))
		return (-1);
	return (0);
}

static int	convert_xmp(void *mlx_ptr, t_texdata *data)
{
	data->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			data->filepath,
			&data->width,
			&data->height);
	if (NULL == data->mlx_img)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR, data->filepath, strerror(errno));
		return (1);
	}
	free(data->filepath);
	data->filepath = NULL;
	data->addr = mlx_get_data_addr(data->mlx_img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	if (NULL == data->addr)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	return (0);
}
