#include "cub3d.h"

static void	update_monster(t_c3_env *env, t_entity *entity)
{
	double	dist;

	dist = ft_euclidean_dist(entity->pos, env->player.pos);
	if (dist < 0.5)
	{
		env->player.pos.x = env->player.pos.x + env->player.dir.x * 0.1;
		env->player.pos.y = env->player.pos.y + env->player.dir.y * 0.1;
	}
}

static void	update_boxes(t_c3_env *env, t_entity *entity)
{
	double	dist;

	dist = ft_euclidean_dist(entity->pos, env->player.pos);
	if (dist < 0.5)
	{
		env->player.pos.x = env->player.pos.x + env->player.dir.x * 0.1;
		env->player.pos.y = env->player.pos.y + env->player.dir.y * 0.1;
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
}
