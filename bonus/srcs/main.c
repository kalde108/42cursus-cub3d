#include "mlx.h"
#include "cub3d.h"

# include <stdlib.h>
# include <stdio.h>

int	g_debug = 0;

void DISPLAY_SHORT_MAP(t_c3_env *env); //REMOVE
void MEMORY_MAP(t_c3_env *env); //REMOVE

static void	TEST(t_c3_env *env)
{
	srand(time(NULL));
	env->entity_count = 0;
	env->entities[0] = (t_entity){MONSTER, (t_v2d_d){26.5, 12.5}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){12.5, 26.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[1] = (t_entity){BOXES, (t_v2d_d){26.5, 10.5}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){10.5, 26.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[2] = (t_entity){BOXES, (t_v2d_d){26.7, 5.2}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 26.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[3] = (t_entity){BOXES, (t_v2d_d){24.13, 5.3}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[4] = (t_entity){BOXES, (t_v2d_d){24.6, 5.5}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[5] = (t_entity){BOXES, (t_v2d_d){24.2, 5.9}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[6] = (t_entity){BOXES, (t_v2d_d){24.8, 5.4}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
	env->entities[7] = (t_entity){BOXES, (t_v2d_d){24.7, 5.8}, (t_v2d_d){-1, 0}, (t_v2d_d){0, 0}, MONSTER_MOVEMENT_SPEED, MONSTER_ROTATION_SPEED, ft_euclidean_dist((t_v2d_d){6.5, 24.5}, env->player.camera.pos), env->scene.elems[WALL] + 2};
	env->entity_count++;
}

// 137422175504
//            -
// 137417863776
//      4311728


int	main(int ac, char **av)
{
	t_c3_env	env;

	srand(time(NULL));
	env = (t_c3_env){0};
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
