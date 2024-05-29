#include <stdlib.h>

#include "cub3d.h"
#include "update.h"

static t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame);
static void	update_basic_frames(t_c3_env *env);

void	update_frames(t_c3_env *env)
{
	update_basic_frames(env);
	update_portal_frames(env->scene.elems[BASIC_TEXTURE]);
}

static void	update_basic_frames(t_c3_env *env)
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
}

static t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame)
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
