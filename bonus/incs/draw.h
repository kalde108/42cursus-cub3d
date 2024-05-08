/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:50:50 by ibertran         ###   ########lyon.fr   */
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

t_tex	get_wall_texture(int side, t_v2d_d ray_dir, t_tex *textures);

#endif