#include "hud.h"

void	hud(t_c3_env *env)
{
	crosshair(env);
	interaction_cooldown(env);
	if (env->options.minimap.enable)
		minimap(env);
}
