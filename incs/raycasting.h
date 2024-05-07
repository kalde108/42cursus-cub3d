#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"	// t_v2d_d, t_v2d_i
# include "draw.h"	// t_vline

typedef struct s_ray
{
	t_v2d_d	ray_dir;
	t_v2d_d	delta_dist;
	t_v2d_i	map_pos;
	t_v2d_i	step;
	t_v2d_d	side_dist;
	int		side;
	double	perp_wall_dist;
}	t_ray;

void	ray_calculation(t_player *player, t_ray *ray, int x);
void	ft_dda(t_cubscene *scene, t_ray *ray);
int		get_tex_x(t_ray *ray, int width, t_player player);
void	get_line_y(t_vline *line, double perp_wall_dist);


#endif
