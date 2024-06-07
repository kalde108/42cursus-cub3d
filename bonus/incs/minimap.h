#ifndef MINIMAP_H
# define MINIMAP_H

# include "ft_math.h"

# define MINIMAP_X 150
# define MINIMAP_Y 150
# define MINIMAP_SIZE 200
# define MINIMAP_ZOOM 15.0
# define MINIMAP_BORDER_COLOR (t_color){0x00000000}

# define MINIMAP_LOCK 0

# define TEST_ANGLE PI / 4

void	draw_view_cone(t_c3_env *env);

#endif