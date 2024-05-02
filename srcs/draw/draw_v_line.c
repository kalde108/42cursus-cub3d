#include "cub3d.h"

void	draw_v_line(t_c3_env *env, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		*(unsigned int *)(env->img.addr + (y * env->img.line_length + x * (env->img.bits_per_pixel / 8))) = color;
		y++;
	}
}