#ifndef PLAYER_H
# define PLAYER_H

# include "ft_math.h"

# define PLAYER_MOVEMENT_SPEED 0.03
# define PLAYER_ROTATION_SPEED 0.01
# define PLAYER_SIZE 0.1

typedef struct s_player
{
	t_v2d_d	pos;	// player position
	t_v2d_d	dir;	// player orientation
	t_v2d_d	plane;	// camera plane
	double	mv_speed;
	double	rt_speed;
}	t_player;

#endif //PLAYER_H
