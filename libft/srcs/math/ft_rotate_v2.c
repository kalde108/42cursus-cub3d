#include <math.h>

#include "ft_math.h"

void	ft_rotate_v2(t_v2d_d *v, double angle)
{
	double	old_x;

	old_x = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = old_x * sin(angle) + v->y * cos(angle);
}
