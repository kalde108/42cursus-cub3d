#include "mlx.h"
#include "cub3d.h"
#include "draw.h"
#include "key_index.h"
#include <math.h>

# include <stdio.h>
# include <stdlib.h>

char	test_map[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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

void	update_pos(t_c3_env *env)
{
	if (env->key_state[KEY_W])
	{
		if (test_map[(int)(env->pos.x + env->dir.x * env->move_speed)][(int)env->pos.y] == 0)
			env->pos.x += env->dir.x * env->move_speed;
		if (test_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * env->move_speed)] == 0)
			env->pos.y += env->dir.y * env->move_speed;
	}
	if (env->key_state[KEY_S])
	{
		if (test_map[(int)(env->pos.x - env->dir.x * env->move_speed)][(int)env->pos.y] == 0)
			env->pos.x -= env->dir.x * env->move_speed;
		if (test_map[(int)env->pos.x][(int)(env->pos.y - env->dir.y * env->move_speed)] == 0)
			env->pos.y -= env->dir.y * env->move_speed;
	}
	if (env->key_state[KEY_A])
	{
		if (test_map[(int)(env->pos.x - env->dir.y * env->move_speed)][(int)env->pos.y] == 0)
			env->pos.x -= env->dir.y * env->move_speed;
		if (test_map[(int)env->pos.x][(int)(env->pos.y + env->dir.x * env->move_speed)] == 0)
			env->pos.y += env->dir.x * env->move_speed;
	}
	if (env->key_state[KEY_D])
	{
		if (test_map[(int)(env->pos.x + env->dir.y * env->move_speed)][(int)env->pos.y] == 0)
			env->pos.x += env->dir.y * env->move_speed;
		if (test_map[(int)env->pos.x][(int)(env->pos.y - env->dir.x * env->move_speed)] == 0)
			env->pos.y -= env->dir.x * env->move_speed;
	}
	if (env->key_state[KEY_LEFT])
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(env->rot_speed) - env->dir.y * sin(env->rot_speed);
		env->dir.y = old_dir_x * sin(env->rot_speed) + env->dir.y * cos(env->rot_speed);
		old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(env->rot_speed) - env->plane.y * sin(env->rot_speed);
		env->plane.y = old_plane_x * sin(env->rot_speed) + env->plane.y * cos(env->rot_speed);
	}

	if (env->key_state[KEY_RIGHT])
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(-env->rot_speed) - env->dir.y * sin(-env->rot_speed);
		env->dir.y = old_dir_x * sin(-env->rot_speed) + env->dir.y * cos(-env->rot_speed);
		old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(-env->rot_speed) - env->plane.y * sin(-env->rot_speed);
		env->plane.y = old_plane_x * sin(-env->rot_speed) + env->plane.y * cos(-env->rot_speed);
	}
}

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

		int line_height;
		int draw_start;
		int draw_end;

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

		if (perp_wall_dist == 0)
			line_height = HEIGHT;
		else
			line_height = (int)(HEIGHT / perp_wall_dist);
		// line_height = (int)(HEIGHT / dist_to_wall(&map_pos, delta_dist, step, side_dist));

		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		int color;

		if (test_map[map_pos.x][map_pos.y] == 1)
			color = 0x00FF0000;
		else if (test_map[map_pos.x][map_pos.y] == 2)
			color = 0x0000FF00;
		else if (test_map[map_pos.x][map_pos.y] == 3)
			color = 0x000000FF;
		else if (test_map[map_pos.x][map_pos.y] == 4)
			color = 0x00FFFF00;
		else
			color = 0x00FFFFFF;
	
		if (side == 1)
			color = color / 2;
		// else if (ray_dir.y > 0)
		// 	color = color / 4;
		
		draw_v_line(env, x, draw_start, draw_end, color);
		x++;
	}
}

int	render(t_c3_env *env)
{
	// printf("render\n");
	clean_screen(env);

	update_pos(env);

	simple_raycasting(env);

	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
