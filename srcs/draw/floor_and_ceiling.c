#include "cub3d.h"

// inline void	clean_screen(t_c3_env *env)
static void	draw_ceiling(t_c3_env *env)
{
	register int			cursor;
	static const int		max = (HEIGHT * (WIDTH >> 2)) >> 1;
	__int128_t				*img_ptr;
	static const __int128_t	color = ((__int128_t)0x2d44a0 << 96) + ((__int128_t)0x2d44a0 << 64) + \
								((__int128_t)0x2d44a0 << 32) + ((__int128_t)0x2d44a0);

	img_ptr = (__int128_t *)env->img.addr;
	cursor = -1;
	while (++cursor < max)
	{
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor] = color;
	}
}

// inline void	clean_screen(t_c3_env *env)
static void	draw_floor(t_c3_env *env)
{
	register int			cursor;
	static const int		max = (HEIGHT * (WIDTH >> 2));
	__int128_t				*img_ptr;
	static const __int128_t	color = ((__int128_t)0xbc8128 << 96) + ((__int128_t)0xbc8128 << 64) + \
								((__int128_t)0xbc8128 << 32) + ((__int128_t)0xbc8128);

	img_ptr = (__int128_t *)env->img.addr;
	cursor = ((HEIGHT * (WIDTH >> 2)) >> 1) - 1;
	while (++cursor < max)
	{
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor++] = color;
		img_ptr[cursor] = color;
	}
}

void	floor_and_ceiling(t_c3_env *env)
{
	draw_ceiling(env);
	draw_floor(env);
}
