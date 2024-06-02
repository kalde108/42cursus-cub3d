#ifndef CAMERA_H
# define CAMERA_H

# include "ft_math.h"

typedef struct s_camera
{
	t_v2d_d	pos;
	t_v2d_d	dir;
	t_v2d_d	plane;
}	t_camera;

#endif