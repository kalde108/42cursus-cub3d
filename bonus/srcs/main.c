/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:49 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/22 22:32:15 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

# include "entity.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include "tile_address.h"

void DISPLAY_SHORT_MAP(t_c3_env *env); //REMOVE

static void	TEST(t_c3_env *env)
{
	env->entity_count = 0;
	env->entities[0] = (t_entity){MONSTER, (t_v2d_d){26.5, 12.5}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){12.5, 26.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[1] = (t_entity){BOXES, (t_v2d_d){26.5, 10.5}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){10.5, 26.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[2] = (t_entity){BOXES, (t_v2d_d){26.7, 5.2}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 26.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[3] = (t_entity){BOXES, (t_v2d_d){24.13, 5.3}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[4] = (t_entity){BOXES, (t_v2d_d){24.6, 5.5}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[5] = (t_entity){BOXES, (t_v2d_d){24.2, 5.9}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[6] = (t_entity){BOXES, (t_v2d_d){24.8, 5.4}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[7] = (t_entity){BOXES, (t_v2d_d){24.7, 5.8}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	init_timer(&env->clocks.map_tex_timer, 100, AUTO_RESET);
	env->scene.elems[WALL][3].options = 1;
	env->scene.elems[FLOOR][3].options = 0;
	env->scene.portals.tab[0].is_open = 1;
	env->scene.portals.tab[1].is_open = 1;
	env->scene.portals.tab[0].linked_portal = 1;
	env->scene.portals.tab[1].linked_portal = 0;
	env->scene.portals.tab[0].face = 0;
	env->scene.portals.tab[1].face = 0;
	env->scene.portals.opened_count = 2;
	env->scene.portals.opened[0] = 0;
	env->scene.portals.opened[1] = 1;
	// env->scene.portals.tab[2].is_open = 1;
	// env->scene.portals.tab[3].is_open = 1;
	// env->scene.portals.tab[2].linked_portal = 3;
	// env->scene.portals.tab[3].linked_portal = 2;
	// env->scene.portals.opened_count = 2;
	// env->scene.portals.opened[2] = 2;
	// env->scene.portals.opened[3] = 3;
}

int	main(int ac, char **av)
{
	t_c3_env	env;

	env = (t_c3_env){0};
	if (check_arguments(ac, av) || init_cubenv(&env, av[1]))
		return (1);
	if (load_textures(env.mlx, env.scene.elems) || open_mlx_window(&env))
	{
		destroy_cubenv(&env);
		return (1);
	}
	dprintf(2, "CPUCORES: %d\n", CPUCORES); //DEBUG
	if (pthread_mutex_init(&env.call_mutex, NULL))
	{
		destroy_cubenv(&env);
		return (1);
	}
	TEST(&env);
	DISPLAY_SHORT_MAP(&env);
	mlx_loop(env.mlx);
	destroy_cubenv(&env);
	pthread_mutex_destroy(&env.call_mutex);
	return (0);
}
