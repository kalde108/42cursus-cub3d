#ifndef TEXTURES_H
# define TEXTURES_H

#include "stdbool.h"
#include "stddef.h"

//ATTRIBUTES
# define DEFAULT_FRAMETIME 100
# define DEFAULT_HINDER 0
# define DEFAULT_ANIMATION LOOP
# define DEFAULT_DAMAGE 0
# define DEFAULT_WALKABLE true

# define ATTR_1 "animation="
# define ATTR_2 "frametime="
# define ATTR_3 "framestart="
# define ATTR_4 "walkable="
# define ATTR_5 "hinder="
# define ATTR_6 "damage="

//ERROR MESSAGES
# define INVAL_ATTR "Invalid attribute"

enum e_animation
{
	STILL,
	LOOP,
	SWAY,
	RANDOM
};

typedef struct s_attributes
{
	size_t	frametime;
	int		animation;
	int		damage;
	int		hinder;
	bool	walkable;
}	t_attributes;

#endif