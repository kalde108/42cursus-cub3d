#include "cubscene.h"
#include "cub3d.h"
#include "textures.h"

# include <stdio.h>

t_texdata	*get_current_frame(t_elem *texture, size_t frame_skip);

void	update_frames(t_c3_env *env)
{
	int		i;
	int		j;
	size_t	passed_frame;
	t_elem	*texture;

	// if (get_time() - env->animation_time < 100)
	// 	return ;
	passed_frame = timer_is_over(&env->clocks.map_tex_timer);
	if (!passed_frame)
		return ;
	i = 0;
	while (i < BASIC_TEXTURE)
	{
		j = 0;
		while (j < MAX_TEXTURE)
		{
			texture = env->scene.elems[i] + j;
			if (texture->n > 1)
				texture->current = get_current_frame(texture, passed_frame);
			j++;
		}
		i++;
	}
}

t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame)
{
	texture->current_frame += passed_frame * texture->dir;
	if (texture->options & LOOP)
	{
		texture->current_frame %= texture->n;
		return (texture->frames + texture->current_frame);
	}
	if (texture->current_frame >= texture->n)
	{
		texture->current_frame = texture->n - (texture->n - texture->current_frame + 1);
		texture->dir = -1;
	}
	else if (texture->current_frame < 0)
	{
		texture->current_frame = -texture->current_frame;
		texture->dir = 1;
	}
	return (texture->frames + texture->current_frame);
}
