/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:07:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 14:36:35 by ibertran         ###   ########lyon.fr   */
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

static int	init_texture(t_tex ***texture);
static int	allocate_wall_floor_ceilling(t_tex **type);

int	init_cubenv(t_c3_env *env, char *arg)
{
	env->mlx = mlx_init();
	if (NULL == env->mlx)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	if (0 != init_texture(&env->scene.texture))
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		return (1);
	}
	if (0 != get_cubscene(arg, env))
		// || 0 != get_player_spawn(env->scene, &env->player)
		// || 0 != get_monster_spawn(env.scene, &env->monster)
		// || 0 == is_player_enclosed(&env->scene, &env->player))
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		destroy_scene(&env->scene, env->mlx);
		return (1);
	}
	init_timer(&env->frame_timer, 0, MANUAL_RESET);
	return (0);
}

static int	init_texture(t_tex ***texture)
{
	t_tex	**ptr;
	int		i;

	ptr = ft_calloc(TEXTURES_TYPES, sizeof(t_tex *));
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
	*texture = ptr;
	return (0);
}

static int	allocate_wall_floor_ceilling(t_tex **type)
{
	t_tex	*ptr;

	ptr = ft_calloc(MAX_TEXTURE, sizeof(t_tex));
	if (NULL == ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (1);
	}
	*type = ptr;
	return (0);
}
