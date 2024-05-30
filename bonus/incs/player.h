/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/30 18:03:56 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLAYER_H
# define PLAYER_H

# include "ft_math.h"

# define PLAYER_MOVEMENT_SPEED 2.5
# define PLAYER_ROTATION_SPEED 1.5
# define PLAYER_SIZE 0.1

# define MOUSE_SENSIVITY 0.1

typedef struct s_player
{
	t_v2d_d	pos;	// player position
	t_v2d_d	dir;	// player orientation
	t_v2d_d	plane;	// camera plane
	double	mv_speed;
	double	rt_speed;
}	t_player;

#endif //PLAYER_H
