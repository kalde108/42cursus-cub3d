#include "ft_math.h"
#include <math.h>

double	ft_euclidean_dist(t_v2d_d a, t_v2d_d b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}
