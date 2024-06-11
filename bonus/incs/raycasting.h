/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:02:23 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 17:02:24 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cubscene.h"
# include "player.h"

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
	int		cell;
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

void		ray_calculation(t_camera *camera, t_ray *ray);
void		ft_dda(t_cubscene *scene, t_ray *ray);

void		portal_hit_move(
				t_cubscene *scene,
				t_ray *ray,
				t_camera *camera,
				double *move);
void		portal_hit(t_cubscene *scene, t_ray *ray, t_camera *camera);

t_texdata	*get_wall_texture(t_cubscene *scene, int cell, t_elem **textures);
int			get_tex_x(t_ray *ray, int width, t_camera *camera);
void		get_line_y(t_hit_buffer *hit_buff, double perp_wall_dist);

void		screen_ray_calculation(t_camera *camera, t_ray *ray, int x);
void		single_raycast(
				t_cubscene *scene,
				t_camera camera,
				t_hit_buffer hit_buf[MAX_LAYERS]);

int			get_relative_position(int f1, int f2);
void		camera_rotation(t_camera *camera, double angle);

#endif
