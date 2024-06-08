#include <math.h>

#include "ft_math.h"

double	player_angle(t_v2d_d player)
{
	double	magnitude;
	double	cos_angle;
	double	angle;

	magnitude = sqrt(-player.x * -player.x + -player.y * -player.y);
	cos_angle = -player.y / magnitude;
	if (cos_angle > 1.0)
		cos_angle = 1.0;
	if (cos_angle < -1.0)
		cos_angle = -1.0;
	angle = acos(cos_angle);
	if (player.x < 0)
		angle = -angle;
	return (angle);
}
