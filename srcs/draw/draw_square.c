#include "draw.h"

void	draw_square(t_c3_env *env, int x, int y, int size, int color)
{
	int	half_size;
	int	i;
	int	j;

	half_size = size / 2;
	i = -half_size;
	while (i < half_size)
	{
		j = -half_size;
		while (j < half_size)
		{
			put_pixel(env, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
