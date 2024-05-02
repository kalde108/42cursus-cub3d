#include "cub3d.h"

void	put_pixel(t_c3_env *env, int x, int y, int color)
{
	char	*dst;

	dst = env->img.addr + (y * env->img.line_length + x * (env->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
