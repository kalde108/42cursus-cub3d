/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:49 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 17:56:49 by kchillon         ###   ########lyon.fr   */
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
	DISPLAY_SHORT_MAP(&env);
	mlx_loop(env.mlx);
	dprintf(2, "mlx_loop ended\n");
	destroy_cubenv(&env);
	return (0);
}
