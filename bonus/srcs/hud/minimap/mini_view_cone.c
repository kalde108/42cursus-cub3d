/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_view_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:48:57 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:48:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

void	mini_view_cone(t_c3_env *env)
{
	int				x;
	int				hit_count;
	t_hit_buffer	*hit_buf;

	x = 0;
	while (x < WIDTH)
	{
		hit_count = env->buffer[x]->count;
		hit_buf = env->buffer[x];
		view_cone_x(env, x, hit_count, hit_buf);
		x++;
	}
}
