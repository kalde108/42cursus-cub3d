/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:20:25 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/08 18:36:29 by ibertran         ###   ########lyon.fr   */
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
#include "color.h"

static int	load_basic_textures(void *mlx_ptr, t_elem **textures);
static int	load_portal_textures(void *mlx_ptr, t_elem *textures);
static int	convert_xpm(void *mlx_ptr, t_texdata *data);

int	load_textures(void *mlx_ptr, t_elem **textures)
{
	int	status;

	ft_dprintf(STDERR_FILENO, "LOADING TEXTURES...\n");
	status = 0;
	status = load_basic_textures(mlx_ptr, textures);
	if (0 == status)
		status = load_portal_textures(mlx_ptr, textures[PORTAL]);
	ft_dprintf(STDERR_FILENO, "\n");
	return (status);
}


static int	load_basic_textures(void *mlx_ptr, t_elem **textures)
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
				if (convert_xpm(mlx_ptr, textures[i][j].frames + k))
					return (-1);
				if (NULL == textures[i][j].current)
					textures[i][j].current = textures[i][j].frames;
				textures[i][j].dir = 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	load_portal_textures(void *mlx_ptr, t_elem *textures)
{
	int	i;

	if (0 == textures->n)
		return (0);
	i = 0;
	while (i < textures->n)
	{
		if (convert_xpm(mlx_ptr, textures->frames + i))
			return (-1);
		i++;
	}
	if (NULL == textures->current)
		textures->current = textures->frames;
	textures->dir = 1;
	return (0);
}

static int	convert_xpm(void *mlx_ptr, t_texdata *data)
{
	ft_dprintf(STDERR_FILENO, "\t%s: ", data->filepath);
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
	data->addr = (t_color *)mlx_get_data_addr(data->mlx_img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	data->average_color = get_average_color(data->addr,
			data->width * data->height);
	if (NULL == data->addr)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	ft_dprintf(STDERR_FILENO, "OK\n");
	return (0);
}
