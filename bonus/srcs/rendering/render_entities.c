#include "cub3d.h"

void	render_entities(t_c3_env *env)
{
	// size_t	i;
	// t_entity	*entity;
	// t_vline		line;
	// t_texdata	*texture;
	// int			tex_x;

	// i = 0;
	// while (i < env->entity_count)
	// {
	// 	entity = &env->entities[i];
	// 	if (entity->type == ENTITY_TYPE_ENEMY)
	// 	{
	// 		line.x = entity->x - entity->size / 2;
	// 		while (line.x < entity->x + entity->size / 2)
	// 		{
	// 			texture = get_entity_texture(entity->id, env->textures);
	// 			tex_x = get_tex_x_entity(entity, texture->width);
	// 			get_line_y_entity(&line, entity, env->player);
	// 			draw_v_line_entity(&env->img, &line, tex_x, texture);
	// 			line.x++;
	// 		}
	// 	}
	// 	i++;
	// }
}