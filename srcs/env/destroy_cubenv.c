/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cubenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:49:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/05 03:41:21 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "cub3d.h"
#include "cubscene.h"

static void	ft_mlx_free(t_c3_env *env);

void	destroy_cubenv(t_c3_env *env)
{
	destroy_scene(&env->scene, env->mlx);
	ft_mlx_free(env);
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
