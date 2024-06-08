#include "cub3d.h"
#include "options.h"

void	cub_options(t_c3_env *env)
{
	op_minimap_enable(env);
	op_minimap_lock(env);
	op_minimap_zoom(env);
	op_minimap_pos(env);
	op_minimap_size(env);
	op_minimap_view(env);
	op_fps(env);
}
