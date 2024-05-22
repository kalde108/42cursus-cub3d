#include <stdlib.h>

#include "cubscene.h"
#include "cub3d.h"
#include "textures.h"

# include <stdio.h>

t_texdata	*get_current_frame(t_elem *texture, size_t frame_skip);
void	update_special_frames(t_elem **elems, size_t passed_frame);

void	update_frames(t_c3_env *env)
{
	int		i;
	int		j;
	size_t	passed_frame;
	t_elem	*texture;

	i = 0;
	while (i < BASIC_TEXTURE)
	{
		j = 0;
		while (j < MAX_TEXTURE)
		{
			texture = env->scene.elems[i] + j;
			if (texture->n > 1 && texture->attr.animation != NONE)
			{
				passed_frame = timer_is_over(&texture->timer);
				if (passed_frame > 0)
					texture->current = get_current_frame(texture, passed_frame);
			}
			j++;
		}
		i++;
	}
	update_special_frames(env->scene.elems + BASIC_TEXTURE, passed_frame);
}

t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame)
{
	texture->current_frame += passed_frame * texture->dir;
	if (texture->attr.animation == LOOP)
	{
		texture->current_frame %= texture->n;
		return (texture->frames + texture->current_frame);
	}
	if (texture->attr.animation == SWAY)
	{
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
	return (texture->frames + (rand() % texture->n));	
}

void	update_special_frames(t_elem **elems, size_t passed_frame)
{
	int i;

	i = 0;
	while (i < SPECIAL_TEXTURES)
	{
		if (elems[i]->n > 1 && elems[i]->attr.animation != NONE)
		{
			elems[i]->current = get_current_frame(elems[i], passed_frame);
		}
		i++;
	}
}
