/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:01:58 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 17:01:59 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "cub3d.h"

void	op_fps(t_c3_env *env);
void	op_minimap_enable(t_c3_env *env);
void	op_minimap_lock(t_c3_env *env);
void	op_minimap_pos(t_c3_env *env);
void	op_minimap_size(t_c3_env *env);
void	op_minimap_view(t_c3_env *env);
void	op_minimap_zoom(t_c3_env *env);

#endif