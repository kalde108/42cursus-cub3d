/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:20:25 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/06 05:55:31 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "libft.h"
#include "cubscene.h"
#include "mlx.h"
#include "parsing.h"

static int	convert_xmp(void *mlx_ptr, t_tex *texture);

int	load_textures(void *mlx_ptr, t_cubscene *scene)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (convert_xmp(mlx_ptr, scene->texture + i))
			ft_dprintf(STDERR_FILENO,
			MLX_ERR,
			scene->texture[i].filepath,
			strerror(errno));
		i++;
	}
	return (0);
}

static int	convert_xmp(void *mlx_ptr, t_tex *texture)
{
	texture->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			texture->filepath,
			&texture->width,
			&texture->height);
	if (NULL == texture->mlx_img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->mlx_img,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	if (NULL == texture->addr)
		return (1);
	return (0);
}
