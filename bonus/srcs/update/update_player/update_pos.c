#include <math.h>

#include "cub3d.h"
#include "key_index.h"
#include "tile_address.h"
#include "raycasting.h"

# include <stdio.h>

static t_v2d_d	get_move_dir(t_c3_env *env)
{
	t_v2d_d	move_dir;
	
	move_dir = (t_v2d_d){0, 0};
	move_dir.x = (env->key_state[KEY_W] - env->key_state[KEY_S]) * env->player.dir.x + \
		(env->key_state[KEY_A] - env->key_state[KEY_D]) * env->player.dir.y;
	move_dir.y = (env->key_state[KEY_W] - env->key_state[KEY_S]) * env->player.dir.y - \
		(env->key_state[KEY_A] - env->key_state[KEY_D]) * env->player.dir.x;
	if ((env->key_state[KEY_W] || env->key_state[KEY_S]) && (env->key_state[KEY_A] || env->key_state[KEY_D]))
	{
		move_dir.x *= SQRT2_2;
		move_dir.y *= SQRT2_2;
	}
	return (move_dir);

}

static t_v2d_d	get_move_vec(t_c3_env *env)
{
	t_v2d_d	move_dir;
	t_v2d_d	move_vec;
	
	move_dir = get_move_dir(env);
	move_vec.x = move_dir.x * env->player.mv_speed;
	move_vec.y = move_dir.y * env->player.mv_speed;
	return (move_vec);
}

void	update_pos(t_c3_env *env)
{
	t_ray	ray;
	t_v2d_d	hit_pos;
	int		hit_count;

	t_v2d_d	move_vec;
	double	move_goal;
	// t_v2d_d	offset;
	t_camera	camera;
	// int			cell;

	move_vec = get_move_vec(env);
	move_goal = sqrt(move_vec.x * move_vec.x + move_vec.y * move_vec.y);
	if (move_goal == 0)
		return ;

	camera.pos = env->player.pos;
	camera.dir = move_vec;
	ray.total_perp_wall_dist = 0;
	ray.hit_type = 0;
	hit_count = 0;
	while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
	{
		if (IS_PORTAL(ray.hit_type))
			portal_hit(&env->scene, &ray, &camera);
		ray_calculation(&camera, &ray);
		ft_dda(&env->scene, &ray);
		hit_pos = (t_v2d_d){camera.pos.x + ray.perp_wall_dist * camera.dir.x, \
			camera.pos.y + ray.perp_wall_dist * camera.dir.y};
		if (fabs(hit_pos.x - env->player.pos.x) < fabs(move_vec.x) + PLAYER_SIZE)
		{
			env->player.pos.x += move_vec.x;
			move_vec.x = 0;
		}
		// if (ray.perp_wall_dist > (move_goal + PLAYER_SIZE))
		// {
		// 	env->player.pos.x += move_vec.x;
		// 	env->player.pos.y += move_vec.y;
		// 	return ;
		// }
		// else
		// {
		// 	move_goal -= ray.perp_wall_dist;
		// 	camera.pos.x += ray.perp_wall_dist * camera.dir.x;
		// 	camera.pos.y += ray.perp_wall_dist * camera.dir.y;
		// }
		hit_count++;
	}
	// move_vec = get_move_vec(env);
	// offset.x = ((move_vec.x >= 0) - (move_vec.x < 0)) * PLAYER_SIZE;
	// offset.y = ((move_vec.y >= 0) - (move_vec.y < 0)) * PLAYER_SIZE;
	// cell = env->scene.map[(int)env->player.pos.y * env->scene.width + \
	//  	(int)(env->player.pos.x + move_vec.x + offset.x)];
	// if (NOT_WALL(cell) && !IS_PORTAL(cell))
	// 	env->player.pos.x += move_vec.x;
	// cell = env->scene.map[(int)(env->player.pos.y + move_vec.y + offset.y) * \
	// 	env->scene.width + (int)env->player.pos.x];
	// if (NOT_WALL(cell) && !IS_PORTAL(cell))
	// 	env->player.pos.y += move_vec.y;
}
