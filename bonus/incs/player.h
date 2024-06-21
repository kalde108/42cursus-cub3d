/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:02:19 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/19 18:20:03 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "camera.h"
# include "ft_time.h"
# include "stdbool.h"

# define PLAYER_WALKING_SPEED 2.5
# define PLAYER_RUNNING_SPEED 5.0
# define PLAYER_ROTATION_SPEED 1.5
# define PLAYER_SIZE 0.1
# define PORTAL_OFFSET 0.001

# define MOUSE_SENSIVITY 0.1

# define INTERACTION_COOLDOWN 625
# define INTERACTION_DISTANCE 1.0

typedef struct s_player
{
	t_camera	camera;
	double		mv_speed;
	double		rt_speed;
	t_timer		interact;
	bool		succesful_interact;
}	t_player;

#endif //PLAYER_H
