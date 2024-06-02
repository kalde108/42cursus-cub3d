/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/02 16:37:42 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLAYER_H
# define PLAYER_H

# include "camera.h"

# define PLAYER_MOVEMENT_SPEED 2.5
# define PLAYER_ROTATION_SPEED 1.5
# define PLAYER_SIZE 0.1

# define MOUSE_SENSIVITY 0.1

typedef struct s_player
{
	
	t_camera	camera;
	double	mv_speed;
	double	rt_speed;
}	t_player;

#endif //PLAYER_H
