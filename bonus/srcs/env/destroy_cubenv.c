/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cubenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:49:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/16 16:35:56 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "cub3d.h"

static void	free_hit_buffer(t_c3_env *env);
static void	ft_mlx_free(t_c3_env *env);

void	destroy_cubenv(t_c3_env *env)
{
	destroy_scene(&env->scene, env->mlx);
	free_hit_buffer(env);
	ft_mlx_free(env);
}

static void	free_hit_buffer(t_c3_env *env)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		free(env->buffer[i]);
		i++;
	}
	free(env->buffer);
}

static void	ft_mlx_free(t_c3_env *env)
{
	if (env->img.img)
		mlx_destroy_image(env->mlx, env->img.img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	if (env->mlx)
		free(env->mlx);
}
