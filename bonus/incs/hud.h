/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:01:23 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 17:01:24 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "cub3d.h"

void	crosshair(t_c3_env *env);
void	interaction_cooldown(t_c3_env *env);
void	minimap(t_c3_env *env);

#endif