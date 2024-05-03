#include "cub3d.h"

void	draw_v_line(t_c3_env *env, int x, int start, int end, int color)
{
	int	y;
	unsigned int	*dst;
	// unsigned int	*end_dst;

	// dst = (unsigned int *)(env->img.addr + (start << 13) + (x << 2));
	// end_dst = (unsigned int *)(env->img.addr + (end << 13) + (x << 2));
	// while (dst < end_dst)
	// {
	// 	*dst = color;
	// 	dst += 2048;
	// }
	dst = (unsigned int *)env->img.addr;
	y = start;
	while (y < end)
	{
		dst[(y << 11) + x] = color;
		y++;
	}
}
