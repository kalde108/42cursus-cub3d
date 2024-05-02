#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

void	clean_screen(t_c3_env *env);
void	put_pixel(t_c3_env *env, int x, int y, int color);
void	draw_square(t_c3_env *env, int x, int y, int size, int color); // test

#endif