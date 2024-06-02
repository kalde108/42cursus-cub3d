#include "textures.h"

void init_attributes(t_attributes *ptr)
{
	t_attributes	init;

	init.frametime = DEFAULT_FRAMETIME;
	init.animation = DEFAULT_ANIMATION;
	init.damage = DEFAULT_DAMAGE;
	init.hinder = DEFAULT_HINDER;
	init.walkable = DEFAULT_WALKABLE;
	*ptr = init;
}