#ifndef PLAYER_H
# define PLAYER_H

# include "camera.h"
# include "ft_time.h"

# define PLAYER_MOVEMENT_SPEED 2.5
# define PLAYER_ROTATION_SPEED 1.5
# define PLAYER_SIZE 0.1

# define MOUSE_SENSIVITY 0.1

# define INTERACTION_COOLDOWN 1500
# define INTERACTION_DISTANCE 1.0

typedef struct s_player
{
	
	t_camera	camera;
	double	mv_speed;
	double	rt_speed;
	t_timer	interact;
}	t_player;

#endif //PLAYER_H
