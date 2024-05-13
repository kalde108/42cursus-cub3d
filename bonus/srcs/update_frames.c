#include "cubscene.h"
#include "cub3d.h"

# include <stdio.h>

t_texdata	*get_current_frame(t_tex *texture);

void	update_frames(t_c3_env *env)
{
	int		i;
	int		j;
	t_tex	*texture;

	if (get_time() - env->animation_time < 100)
		return ;
	i = 0;
	while (i < BASIC_TEXTURE)
	{
		j = 0;
		while (j < MAX_TEXTURE)
		{
			texture = env->scene.texture[i] + j;
			if (texture->n > 1)
				texture->current = get_current_frame(texture);
			j++;
		}
		i++;
	}
	env->animation_time = get_time();
}

t_texdata	*get_current_frame(t_tex *texture)
{
	texture->next += texture->dir;
	if (texture->n - 1 == texture->next)
		texture->dir = -1;
	else if (0 == texture->next)
		texture->dir = 1;
	return (texture->frames + texture->next);
}
