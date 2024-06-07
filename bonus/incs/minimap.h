#ifndef MINIMAP_H
# define MINIMAP_H

# include "ft_math.h"

# define MINIMAP_LOCK true
# define MINIMAP_X 150
# define MINIMAP_Y 150
# define MINIMAP_SIZE 200
# define MINIMAP_ZOOM 15.0
# define MINIMAP_BORDER_COLOR (t_color){0x00000000}

double	player_angle(t_v2d_d player);
t_color	get_tile_color(t_c3_env *env, int cell);
int		is_on_minimap(t_c3_env *env, int x, int y);

// debug
void	draw_view_cone(t_c3_env *env, double angle);

#endif