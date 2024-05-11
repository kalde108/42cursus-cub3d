/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 18:21:07 by kchillon         ###   ########lyon.fr   */
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

void	draw_v_line(t_img *img, t_vline *line, int tex_x, t_texdata *texture);
void	floor_and_ceiling(t_c3_env *env);

t_texdata	*get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_tex **textures);

#endif