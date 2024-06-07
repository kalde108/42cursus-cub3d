#include "update.h"
#include "tile_address.h"

void	DISPLAY_SHORT_MAP(t_c3_env *env); //REMOVE

static int	get_interaction_cell(t_c3_env *env);

void	player_interaction(t_c3_env *env)
{
	static bool	key_release = true;
	int			cell;

	if (env->key_state[KEY_E])
	{
		if (true == key_release && 0 != timer_is_over(&env->player.interact))
		{
			cell = get_interaction_cell(env);
			if (EMPTY_CELL != cell)
			{
				start_timer(&env->player.interact);
				env->player.succesful_interact = update_portal_status(&env->scene.portals, GET_PORTAL(cell));
			}
		}
		key_release = false;
	}
	else
		key_release = true;
}

static int	get_interaction_cell(t_c3_env *env)
{
	t_hit_buffer	hit_buf[MAX_LAYERS];

	single_raycast(&env->scene, env->player.camera, hit_buf);
	if (IS_PORTAL(hit_buf->cell) && hit_buf->z <= INTERACTION_DISTANCE)
		return (hit_buf->cell);
	return (EMPTY_CELL);
}
