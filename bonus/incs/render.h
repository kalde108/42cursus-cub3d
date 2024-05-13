/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:43 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/13 23:15:02 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <cub3d.h>

int		draw_backgound(t_c3_env *env);
void	update_player(t_c3_env *env);
void	update_entities(t_c3_env *env);
void	update_frames(t_c3_env *env);
void	draw_minimap(t_c3_env *env);
int		render_map(t_c3_env *env);
void	render_entities(t_c3_env *env);

#endif