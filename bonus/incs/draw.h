/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/07 20:20:10 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

# define SHADOW 0.75

typedef struct s_hit_buffer	t_hit_buffer;

typedef struct s_vline
{
	int		x;
	double		start;
	double		end;
}	t_vline;



void	draw_wall(t_img *img, t_hit_buffer *hit_buff, int x);
void	draw_portal(t_img *img, t_hit_buffer *hit_buff, int x);

void	clean_screen(t_c3_env *env);
void	put_pixel(t_img *img, int x, int y, t_color color);
void	put_pixel_alpha(t_img *img, int x, int y, t_color color);
void	draw_line(t_img *img, int x1, int y1, int x2, int y2, t_color color);
void	draw_line_gradient(t_img *img, int x1, int y1, int x2, int y2, t_color color1, t_color color2);
void	draw_line_minimap(t_img *img, int x1, int y1, int x2, int y2, t_color color, t_c3_env *env);
void	draw_rectangle(t_img *img, t_v2d_i pos, t_v2d_i size, t_color color);

void	draw_crosshair(t_c3_env *env); // test

#endif