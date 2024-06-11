/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:01 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:42:02 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	init_attributes(t_attributes *ptr)
{
	t_attributes	init;

	init.frametime = DEFAULT_FRAMETIME;
	init.animation = DEFAULT_ANIMATION;
	*ptr = init;
}
