/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 13:26:32 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

typedef struct s_vline
{
	int		x;
	int		start;
	int		end;
}	t_vline;

void	draw_v_line(t_img *img, t_vline *line, int tex_x, t_tex *texture);
void	floor_and_ceiling(t_c3_env *env);

void	put_pixel(t_img *img, int x, int y, int color);
void	put_pixel_alpha(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void	draw_line_gradient(t_img *img, int x1, int y1, int x2, int y2, int color1, int color2);

t_tex	get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_tex *textures);

#endif