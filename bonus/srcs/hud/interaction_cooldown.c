#include "draw.h"

void	interaction_cooldown(t_c3_env *env)
{
	size_t	cooldown;

	cooldown = get_elapsed_time(&env->player.interact);
	if (cooldown > INTERACTION_COOLDOWN)
		return ;
	if (env->player.succesful_interact)
		draw_rectangle(&env->img,
			(t_v2d_i){WIDTH / 2 + 20,
			HEIGHT / 2 + 10 - (20 * cooldown / INTERACTION_COOLDOWN / 2)},
			(t_v2d_i){4, 20 * cooldown / INTERACTION_COOLDOWN},
			(t_color){0x00AAAAAA});
	else
		draw_rectangle(&env->img,
			(t_v2d_i){WIDTH / 2 + 20,
			HEIGHT / 2 + 10 - (20 * cooldown / INTERACTION_COOLDOWN / 2)},
			(t_v2d_i){4, 20 * cooldown / INTERACTION_COOLDOWN},
			(t_color){0x00FF0000});
}
