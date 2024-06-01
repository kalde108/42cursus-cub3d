/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:49 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/01 16:00:30 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
# include "entity.h"
# include "libft.h"
# include "tile_address.h"

# include "stdlib.h"
# include <math.h>
# include <stdio.h>

void DISPLAY_SHORT_MAP(t_c3_env *env); //REMOVE
void MEMORY_MAP(t_c3_env *env); //REMOVE

static void	TEST(t_c3_env *env)
{
	srand(time(NULL));
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

	if (env->scene.portals.total >= 2)
	{
		int p1 = 0;
		int p2 = 0;
		while (p1 == p2)
		{
			p1 = rand() % env->scene.portals.total;
			p2 = rand() % env->scene.portals.total;
		}

		env->scene.portals.tab[p1].is_open = 1;
		env->scene.portals.tab[p2].is_open = 1;
		env->scene.portals.tab[p1].linked_portal = p2;
		env->scene.portals.tab[p2].linked_portal = p1;
		env->scene.portals.opened_count = 1;
		env->scene.portals.opened[0] = p1;
		env->scene.portals.opened[1] = p2;
	}
	// env->scene.portals.tab[2].is_open = 1;
	// env->scene.portals.tab[3].is_open = 1;
	// env->scene.portals.tab[2].linked_portal = 3;
	// env->scene.portals.tab[3].linked_portal = 2;
	// env->scene.portals.opened_count = 2;
	// env->scene.portals.opened[2] = 2;
	// env->scene.portals.opened[3] = 3;
}

// 137422175504
//            -
// 137417863776
//      4311728


int	main(int ac, char **av)
{
	t_c3_env	env;

	dprintf(2, "sizeof(t_c3_env): %lu\n", sizeof(t_c3_env)); //DEBUG
	srand(time(NULL));
	env = (t_c3_env){0};
	dprintf(2, "CPUCORES: %d\n", CPUCORES); //DEBUG
	if (check_arguments(ac, av) || init_cubenv(&env, av[1]))
		return (1);
	if (load_textures(env.mlx, env.scene.elems) || open_mlx_window(&env))
	{
		destroy_cubenv(&env);
		return (1);
	}
	if (pthread_mutex_init(&env.call_mutex, NULL))
	{
		destroy_cubenv(&env);
		return (1);
	}
	TEST(&env);
	DISPLAY_SHORT_MAP(&env);
	MEMORY_MAP(&env);
	mlx_loop(env.mlx);
	destroy_cubenv(&env);
	pthread_mutex_destroy(&env.call_mutex);
	return (0);
}
