#include <math.h>

#include "ft_math.h"

void	ft_rotate_v1(double *x, double angle)
{
	*x = *x * cos(angle);
}
