#include "cub3d.h"
#include <stdio.h>
#include <unistd.h>

void	draw_v_line(t_c3_env *env, int x, int start, int end, int tex_x, t_tex texture)
{
	int	y;
	unsigned int	*dst;
	double step	= 1.0 * texture.height / (end - start);
	double tex_y = 0;

	dst = (unsigned int *)env->img.addr;
	y = start;
	while (y < end)
	{
		// usleep(1);
		// tex_y = tex_pos  texture.height;
		dst[(y++ << 11) + x] = *(unsigned int *)(texture.addr + (((int)tex_y * texture.line_length) + tex_x * (texture.bits_per_pixel / 8)));
		tex_y += step;
	}
}
