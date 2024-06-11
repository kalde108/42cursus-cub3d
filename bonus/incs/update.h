/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:39:44 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 14:39:47 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

# include "cub3d.h"

void	cub_options(t_c3_env *env);
void	player_interaction(t_c3_env *env);
void	update_mouse(t_c3_env *env);
void	update_frames(t_c3_env *env);
void	update_player(t_c3_env *env);

void	player_mouvement(t_cubscene *scene, t_player *player, int *key_state);
void	player_rotation(t_player *player, t_mouse *mouse, int *key_state);
void	rotate_player(t_player *player, double angle);
void	update_portal_frames(t_elem *portal_tex);
bool	update_portal_status(t_portals *portals, int id);
void	x_mouvement(t_cubscene *scene, t_player *player, t_v2d_d move_vec,
			t_v2d_d *og_vec);
void	y_mouvement(t_cubscene *scene, t_player *player, t_v2d_d move_vec);

#endif