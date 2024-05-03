#include "cub3d.h"
#include "draw.h"
#include <math.h>

// double	dist_to_wall(t_v2d_i *map_pos, t_v2d_d delta_dist, t_v2d_i step, t_v2d_d side_dist)
// {
// 	int	hit;
// 	int	side;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (side_dist.x < side_dist.y)
// 		{
// 			side_dist.x += delta_dist.x;
// 			map_pos->x += step.x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist.y += delta_dist.y;
// 			map_pos->y += step.y;
// 			side = 1;
// 		}
// 		if (test_map[map_pos->x][map_pos->y] > 0)
// 			hit = 1;
// 	}

// 	if (side == 0)
// 		return (side_dist.x - delta_dist.x);
// 	else
// 		return (side_dist.y - delta_dist.y);
// }

// void	ray_calculation(t_c3_env *env, t_v2d_d	ray_dir)
// {

// }

void	simple_raycasting(t_c3_env *env)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		t_v2d_d	ray_dir;

		ray_dir.x = env->dir.x + env->plane.x * (2 * x / (double)WIDTH - 1);
		ray_dir.y = env->dir.y + env->plane.y * (2 * x / (double)WIDTH - 1);

		t_v2d_d delta_dist;

		if (ray_dir.x == 0)
			delta_dist.x = 1e30;
		else
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = fabs(1 / ray_dir.y);

		t_v2d_i	map_pos;

		map_pos.x = (int)env->pos.x;
		map_pos.y = (int)env->pos.y;

		t_v2d_i step;
		
		t_v2d_d side_dist;

		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (env->pos.x - map_pos.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map_pos.x + 1.0 - env->pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (env->pos.y - map_pos.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map_pos.y + 1.0 - env->pos.y) * delta_dist.y;
		}

		int	hit;
		int	side;

		hit = 0;
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_pos.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_pos.y += step.y;
				side = 1;
			}
			if (test_map[map_pos.x][map_pos.y] > 0)
				hit = 1;
		}

		double	perp_wall_dist;

		if (side == 0)
			perp_wall_dist = side_dist.x - delta_dist.x;
		else
			perp_wall_dist = side_dist.y - delta_dist.y;

		int line_height;

		if (perp_wall_dist == 0)
			line_height = HEIGHT;
		else
			line_height = (int)(HEIGHT / perp_wall_dist);
		// line_height = (int)(HEIGHT / dist_to_wall(&map_pos, delta_dist, step, side_dist));
		
		int draw_start;
		int draw_end;

		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		
		draw_v_line(env, x, draw_start, draw_end, get_color(test_map[map_pos.x][map_pos.y], ray_dir, side, perp_wall_dist));
		x++;
	}
}
