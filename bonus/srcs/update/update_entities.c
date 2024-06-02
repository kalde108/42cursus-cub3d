#include "cub3d.h"

#include <stdlib.h>

# include <stdio.h>

static int	entity_cmp(const void *a, const void *b)
{
	t_entity	*entity_a;
	t_entity	*entity_b;

	entity_a = (t_entity *)a;
	entity_b = (t_entity *)b;
	if (entity_a->distance_to_player < entity_b->distance_to_player)
		return (1);
	else if (entity_a->distance_to_player > entity_b->distance_to_player)
		return (-1);
	return (0);
}

static void	update_monster(t_c3_env *env, t_entity *entity)
{
	double	dist;

	dist = ft_euclidean_dist(entity->pos, env->player.camera.pos);
	entity->distance_to_player = dist;
}

static void	update_boxes(t_c3_env *env, t_entity *entity)
{
	double	dist;

	dist = ft_euclidean_dist(entity->pos, env->player.camera.pos);
	entity->distance_to_player = dist;
}

void	DEBUG_PRINT_ENTITY(t_c3_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->entity_count)
	{
		printf("Entity: %p\n", &env->entities[i]);
		printf("Type: %d\n", env->entities[i].type);
		printf("Pos: %f, %f\n", env->entities[i].pos.x, env->entities[i].pos.y);
		printf("Distance to player: %f\n", env->entities[i].distance_to_player);
		i++;
	}
	
}

void	update_entities(t_c3_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->entity_count)
	{
		if (env->entities[i].type == MONSTER)
			update_monster(env, &env->entities[i]);
		else if (env->entities[i].type == BOXES)
			update_boxes(env, &env->entities[i]);
		i++;
	}
	qsort(env->entities, env->entity_count, sizeof(t_entity), entity_cmp);
	// DEBUG_PRINT_ENTITY(env);
}
