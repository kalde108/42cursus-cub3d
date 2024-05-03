#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"	// t_v2d_d, t_v2d_i

typedef struct s_ray
{
	t_v2d_d	ray_dir;
	t_v2d_d	delta_dist;
	t_v2d_i	map_pos;
	t_v2d_i	step;
	t_v2d_d	side_dist;
	int		side;
}	t_ray;

void	ray_calculation(t_c3_env *env, t_ray *ray, int x);
void	ft_dda(t_ray *ray);
void	get_line_y(int *line_y, double perp_wall_dist);

#endif
