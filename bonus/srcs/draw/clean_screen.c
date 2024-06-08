#include "cub3d.h"

void	clean_screen(t_c3_env *env)
{
	register int			cursor;
	static const int		max = (HEIGHT * (WIDTH >> 2));
	__int128_t				*img_ptr;
	static const __int128_t	min = (__int128_t)0;

	img_ptr = (__int128_t *)env->img.addr;
	cursor = -1;
	while (++cursor < max)
	{
		img_ptr[cursor++] = min;
		img_ptr[cursor++] = min;
		img_ptr[cursor++] = min;
		img_ptr[cursor] = min;
	}
}
