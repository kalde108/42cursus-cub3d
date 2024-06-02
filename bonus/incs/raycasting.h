/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:01 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/02 17:43:35 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cubscene.h"
# include "player.h"

# define MAX_JUMPS 100
# define MAX_LAYERS 10

typedef struct s_camera
{
	t_v2d_d	pos;
	t_v2d_d	dir;
	t_v2d_d	plane;
}	t_camera;

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
	char		count;
	int			cell;
	int			side;
	double		z;
	double		y1;
	double		y2;
	t_camera	camera;
	int			tex_x;
	t_texdata	*texture;
}	t_hit_buffer;

int		get_tex_x(t_ray *ray, int width, t_camera *camera);
void	ft_dda(t_cubscene *scene, t_ray *ray, t_camera *camera);	// camera for debug
void	get_line_y(t_hit_buffer *hit_buff, double perp_wall_dist);
void	portal_hit_move(t_cubscene *scene, t_ray *ray, t_camera *camera, double *move);
void	portal_hit(t_cubscene *scene, t_ray *ray, t_camera *camera);
void	screen_ray_calculation(t_camera *camera, t_ray *ray, int x);
void	ray_calculation(t_camera *camera, t_ray *ray);

#endif
