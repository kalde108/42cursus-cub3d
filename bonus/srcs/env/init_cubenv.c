/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:07:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/08 18:22:03 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mlx.h"
#include "parsing.h"
#include "cub3d.h"
#include "libft.h"
#include "cubdef.h"
#include "minimap.h"

static int	init_texture(t_elem ***texture);
static int	allocate_wall_floor_ceilling(t_elem **type);
static int	allocate_portal(t_elem **portal_ptr);

int	init_cubenv(t_c3_env *env, char *arg)
{
	env->mlx = mlx_init();
	if (NULL == env->mlx)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	if (0 != init_texture(&env->scene.elems))
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		return (1);
	}
	if (0 != get_cubscene(arg, env))
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		destroy_scene(&env->scene, env->mlx);
		return (1);
	}
	init_timer(&env->frame_timer, 0, MANUAL_RESET);
	env->options.minimap.lock = MINIMAP_LOCK;
	env->options.minimap.pos = (t_v2d_i){MINIMAP_X, MINIMAP_Y};
	env->options.minimap.size = MINIMAP_SIZE;
	env->options.minimap.zoom = MINIMAP_ZOOM;
	return (0);
}

static int	init_texture(t_elem ***texture)
{
	t_elem	**ptr;
	int		i;

	ptr = ft_calloc(TEXTURES_TYPES, sizeof(t_elem *));
	if (NULL == ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	i = 0;
	while (i < BASIC_TEXTURE)
	{
		if (0 != allocate_wall_floor_ceilling(ptr + i))
		{
			while (i--)
				free(ptr[i]);
			free(ptr);
			return (1);
		}
		i++;
	}
	if (0 != allocate_portal(ptr + i))
		return (1);
	*texture = ptr;
	return (0);
}

static int	allocate_wall_floor_ceilling(t_elem **type)
{
	t_elem	*ptr;

	ptr = ft_calloc(MAX_TEXTURE, sizeof(t_elem));
	if (NULL == ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	*type = ptr;
	return (0);
}

static int	allocate_portal(t_elem **portal_ptr)
{
	t_elem	*ptr;

	ptr = ft_calloc(1, sizeof(t_elem));
	if (NULL == ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	*portal_ptr = ptr;
	return (0);
}
