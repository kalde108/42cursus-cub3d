/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:43 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 20:09:17 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <cub3d.h>

int	draw_backgound(t_c3_env *env);
void	update_player(t_c3_env *env);
void	draw_minimap(t_c3_env *env);
int		render_map(t_c3_env *env);

#endif