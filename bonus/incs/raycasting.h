/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:01 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/22 20:20:02 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include "draw.h"

# define MAX_JUMPS 100
# define MAX_LAYERS 10

typedef struct s_ray
{
	t_v2d_d	ray_dir;
	t_v2d_d	delta_dist;
	t_v2d_i	map_pos;
	t_v2d_i	step;
	t_v2d_d	side_dist;
	int		side;
	double	perp_wall_dist;
	int		hit_type;
	int		turn;
	double	total_perp_wall_dist;
}	t_ray;

typedef struct s_hit_buffer
{
	int		side;
	int		cell;
	// t_vline	line;
	double	y1;
	double	y2;
	int		tex_x;
	t_texdata	*texture;
}	t_hit_buffer;

void	ray_calculation(t_player *player, t_ray *ray, int x);
void	ft_dda(t_cubscene *scene, t_ray *ray, t_player *player);
int		get_tex_x(t_ray *ray, int width, t_player player);
void	get_line_y(t_hit_buffer *hit_buff, double perp_wall_dist);

#endif
