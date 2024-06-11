/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:50:28 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:50:28 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

void	cub_options(t_c3_env *env)
{
	op_minimap_enable(env);
	op_minimap_lock(env);
	op_minimap_zoom(env);
	op_minimap_pos(env);
	op_minimap_size(env);
	op_minimap_view(env);
	op_fps(env);
}
