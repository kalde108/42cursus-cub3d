/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/11 15:14:37 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLAYER_H
# define PLAYER_H

# include "ft_math.h"

# define PLAYER_MOVEMENT_SPEED 2.5
# define PLAYER_ROTATION_SPEED 1.5
# define PLAYER_SIZE 0.1

# define MONSTER_MOVEMENT_SPEED 2.5
# define MONSTER_ROTATION_SPEED 1.5
# define MONSTER_SIZE 0.1

# define WALLKABLE_CHARSET "0FC"

typedef struct s_entity
{
	t_v2d_d	pos;	// player position
	t_v2d_d	dir;	// player orientation
	t_v2d_d	plane;	// camera plane
	double	mv_speed;
	double	rt_speed;
}	t_entity;

#endif //PLAYER_H
