/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 14:24:52 by ibertran         ###   ########lyon.fr   */
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
	double	start;
	double	end;
}	t_vline;

void	draw_wall(t_img *img, t_hit_buffer *hit_buff, int x);
void	draw_portal(t_img *img, t_hit_buffer *hit_buff, int x);

void	clean_screen(t_c3_env *env);
void	put_pixel(t_img *img, int x, int y, t_color color);
void	put_pixel_alpha(t_img *img, int x, int y, t_color color);
void	draw_line(t_img *img, t_v2d_i p1, t_v2d_i p2, t_color color);
void	draw_line_minimap(t_c3_env *env, t_v2d_i p1, t_v2d_i p2, t_color color);
void	draw_rectangle(t_img *img, t_v2d_i pos, t_v2d_i size, t_color color);
void	draw_triangle(t_img *img, t_triangle tirangle, t_color color);

#endif