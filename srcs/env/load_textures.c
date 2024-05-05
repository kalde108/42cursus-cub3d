/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:20:25 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/05 03:31:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "libft.h"
#include "cubscene.h"
#include "mlx.h"
#include "parsing.h"

int	load_textures(void *mlx_ptr, t_cubscene *scene)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		scene->texture[i].ptr = mlx_xpm_file_to_image(mlx_ptr,
				scene->texture[i].filepath,
				&scene->texture[i].width,
				&scene->texture[i].height);
		if (NULL == scene->texture[i].ptr)
		{
			ft_dprintf(STDERR_FILENO,
				MLX_ERR,
				scene->texture[i].filepath,
				strerror(errno));
			return (1);
		}
		i++;
	}
	return (0);
}
