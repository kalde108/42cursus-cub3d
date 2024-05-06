#include "cub3d.h"

void	draw_v_line(t_c3_env *env, int x, int start, int end, unsigned int color)
{
	int	y;
	unsigned int	*dst;

	dst = (unsigned int *)env->img.addr;
	y = start;
	while (y < end)
		dst[(y++ << 11) + x] = color;
}
