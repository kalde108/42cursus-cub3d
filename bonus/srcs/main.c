/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:49 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 19:41:01 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"


# include <stdio.h>

void DISPLAY_SHORT_MAP(t_c3_env *env); //REMOVE

int	main(int ac, char **av)
{
	t_c3_env	env;

	env = (t_c3_env){0};
	if (check_arguments(ac, av) || init_cubenv(&env, av[1]))
		return (1);
	if (load_textures(env.mlx, &env.scene) || open_mlx_window(&env))
	{
		destroy_cubenv(&env);
		return (1);
	}
	dprintf(2, "CPUCORES: %d\n", CPUCORES);
	if (pthread_mutex_init(&env.call_mutex, NULL))
	{
		destroy_cubenv(&env);
		return (1);
	}
	DISPLAY_SHORT_MAP(&env);
	mlx_loop(env.mlx);
	destroy_cubenv(&env);
	pthread_mutex_destroy(&env.call_mutex);
	return (0);
}
