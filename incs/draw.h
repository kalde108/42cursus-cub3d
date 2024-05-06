#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

void	clean_screen(t_c3_env *env);
void	draw_line(t_img *img, int x1, int x2, int y1, int y2, int color);
void	draw_line_gradient(t_img *img, int x1, int y1, int x2, int y2, int color1, int color2); // test
void	draw_square(t_img *img, int x, int y, int size, int color); // test
void	draw_v_line(t_c3_env *env, int x, int start, int end, int color);
void	floor_and_ceiling(t_c3_env *env);
void	put_pixel(t_img *img, int x, int y, int color);

t_tex	get_wall_texture(int side, t_v2d_d ray_dir, t_tex *textures);

#endif