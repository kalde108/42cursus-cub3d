/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_portal_frames.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:27 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/11 19:34:20 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "textures.h"

static t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame);

void	update_portal_frames(t_elem *portal_tex)
{
	size_t	passed_frame;

	if (portal_tex->n > 1 && portal_tex->attr.animation != NONE)
	{
		passed_frame = timer_is_over(&portal_tex->timer);
		portal_tex->current = get_current_frame(portal_tex, passed_frame);
	}
}

static t_texdata	*get_current_frame(t_elem *texture, size_t passed_frame)
{
	texture->current_frame += passed_frame * texture->dir;
	if (texture->attr.animation == LOOP)
	{
		texture->current_frame %= (texture->n - 1);
		return (texture->frames + 1 + texture->current_frame);
	}
	if (texture->attr.animation == SWAY)
	{
		if (texture->current_frame >= texture->n)
		{
			texture->current_frame = texture->n
				- (texture->n - texture->current_frame + 1);
			texture->dir = -1;
		}
		else if (texture->current_frame < 1)
		{
			texture->current_frame = -texture->current_frame + 1;
			texture->dir = 1;
		}
		return (texture->frames + texture->current_frame);
	}
	return (texture->frames + 1 + (rand() % (texture->n - 1)));
}
