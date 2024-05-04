#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"

#include <math.h>

void	draw_view_cone(t_c3_env *env)
{
	t_ray	ray;
	t_v2d_d	ray_hit;
	int		x;
	double	perp_wall_dist;

	x = 0;
	while (x < WIDTH)
	{
		ray_calculation(env, &ray, x);
		ft_dda(&ray);
		if (ray.side == 0)
			perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
		ray_hit.x = env->player.pos.x + ray.ray_dir.x * perp_wall_dist;
		ray_hit.y = env->player.pos.y + ray.ray_dir.y * perp_wall_dist;
		draw_line(&env->img,
			(int)(env->player.pos.x * MINIMAP_SCALE),
			(int)(env->player.pos.y * MINIMAP_SCALE),
			(int)(ray_hit.x * MINIMAP_SCALE),
			(int)(ray_hit.y * MINIMAP_SCALE),
			0x007F00);
		x++;
	}
}
