/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:07:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/05 20:22:05 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "mlx.h"
#include "parsing.h"
#include "cub3d.h"
#include "libft.h"

int	init_cubenv(t_c3_env *env, char *arg)
{
	env->mlx = mlx_init();
	if (NULL == env->mlx)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR, FATAL, strerror(errno));
		return (1);
	}
	if (0 != get_cubscene(arg, &env->scene)
		|| 0 != get_player_spawn(env->scene, &env->player)
		|| 0 == is_player_enclosed(&env->scene, &env->player))
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		destroy_scene(&env->scene, env->mlx);
		return (1);
	}
	return (0);
}
