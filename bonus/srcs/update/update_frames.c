/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:22 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:42:23 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "update.h"
#include "libft.h"

static t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame);
static void			update_basic_frames(t_c3_env *env);

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
	if (texture->attr.animation == RANDOM)
		return (texture->frames + (rand() % texture->n));
	texture->current_frame += passed_frame * texture->dir;
	if (texture->attr.animation == LOOP)
		texture->current_frame %= texture->n;
	if (texture->attr.animation == SWAY
		&& (texture->current_frame >= texture->n || texture->current_frame < 0))
	{
		if (ft_abs(texture->current_frame) / texture->n & 1)
		{
			texture->current_frame = texture->n \
				- (ft_abs(texture->current_frame) % texture->n + 1);
			texture->dir = (texture->current_frame < 0) \
				- (texture->current_frame >= 0);
		}
		else
		{
			texture->current_frame = ft_abs(texture->current_frame) \
				% texture->n;
			texture->dir = (texture->current_frame >= 0) \
				- (texture->current_frame < 0);
		}
	}
	return (texture->frames + texture->current_frame);
}
