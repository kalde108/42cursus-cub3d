#include "cub3d.h"
#include "draw.h"
#include "raycasting.h"

void	simple_raycasting(t_c3_env *env)
{
	t_ray	ray;
	int		x;
	double	perp_wall_dist;
	int		line_y[2];

	x = 0;
	while (x < WIDTH)
	{
		ray_calculation(env, &ray, x);
		ft_dda(&ray);
		if (ray.side == 0)
			perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
		get_line_y(line_y, perp_wall_dist);
		draw_v_line(env,
			x,
			line_y[0],
			line_y[1],
			get_color(test_map[ray.map_pos.x][ray.map_pos.y],
				ray.ray_dir,
				ray.side,
				perp_wall_dist));
		x++;
	}
}
