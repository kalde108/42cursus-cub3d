#ifndef ENTITY_H
# define ENTITY_H

# include "ft_math.h"
# include "cubscene.h"

# define MONSTER_MOVEMENT_SPEED 2.5
# define MONSTER_ROTATION_SPEED 1.5
# define MONSTER_SIZE 0.1

enum e_entity_type
{
	MONSTER,
	BOXES
};

typedef struct s_entity
{
	char		type;
	t_v2d_d		pos;	// entity position
	t_v2d_d		dir;	// entity orientation
	t_v2d_d		plane;	// camera plane
	double		mv_speed;
	double		rt_speed;
	double		distance_to_player;
	t_tex		*sprites;
}	t_entity;

#endif