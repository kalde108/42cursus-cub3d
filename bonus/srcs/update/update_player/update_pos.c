#include <math.h>

#include "cub3d.h"
#include "key_index.h"
#include "tile_address.h"
#include "raycasting.h"
#include "update.h"

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

static void	update_x(t_cubscene *scene, t_c3_env *env, t_v2d_d move_vec)
{
	t_ray		ray;
	t_camera	camera;
	double		rot;

	rot = 0;
	camera.pos = env->player.pos;
	camera.dir = (t_v2d_d){(move_vec.x >= 0) - (move_vec.x < 0), 0};
	ray.total_perp_wall_dist = 0;
	ray.hit_type = 0;
	while (NOT_WALL(ray.hit_type))
	{
		if (IS_PORTAL(ray.hit_type))
		{
			portal_hit_move(&env->scene, &ray, &camera, &rot);
			rotate_player(&env->player, rot);
			ft_rotate_v2(&move_vec, rot);
		}
		ray_calculation(&camera, &ray);
		ft_dda(scene, &ray);
		if (ray.perp_wall_dist > fabs(move_vec.x) + PLAYER_SIZE)
		{
			camera.pos.x += move_vec.x;
			camera.pos.y += move_vec.y;
			break ;
		}
		else if (ray.perp_wall_dist > PLAYER_SIZE)
		{
			camera.pos.x += (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.x;
			camera.pos.y += (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.y;
			move_vec.x -= (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.x;
			move_vec.y -= (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.y;
		}
	}
	env->player.pos.x = camera.pos.x;
	env->player.pos.y = camera.pos.y;
}

static void	update_y(t_cubscene *scene, t_c3_env *env, t_v2d_d move_vec)
{
	t_ray		ray;
	t_camera	camera;
	double		rot;

	camera.pos = env->player.pos;
	camera.dir = (t_v2d_d){0, (move_vec.y >= 0) - (move_vec.y < 0)};
	ray.total_perp_wall_dist = 0;
	ray.hit_type = 0;
	while (IS_FL_CE(ray.hit_type) || (IS_PORTAL(ray.hit_type) && -1 != scene->portals.tab[GET_PORTAL(ray.hit_type)].linked_portal))
	{
		if (IS_PORTAL(ray.hit_type))
		{
			portal_hit_move(&env->scene, &ray, &camera, &rot);
			rotate_player(&env->player, rot);
			ft_rotate_v2(&move_vec, rot);
		}
		ray_calculation(&camera, &ray);
		ft_dda(scene, &ray);
		if (ray.perp_wall_dist > fabs(move_vec.y) + PLAYER_SIZE)
		{
			camera.pos.x += move_vec.x;
			camera.pos.y += move_vec.y;
			break ;
		}
		else if (ray.perp_wall_dist > PLAYER_SIZE)
		{
			camera.pos.x += (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.x;
			camera.pos.y += (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.y;
			move_vec.x -= (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.x;
			move_vec.y -= (ray.perp_wall_dist - PLAYER_SIZE) * camera.dir.y;
		}
	}
	env->player.pos.y = camera.pos.y;
	env->player.pos.x = camera.pos.x;
}

void	update_pos(t_c3_env *env)
{
	t_v2d_d	move_vec;
	double	move_goal;

	move_vec = get_move_vec(env);
	move_goal = sqrt(move_vec.x * move_vec.x + move_vec.y * move_vec.y);
	if (move_goal == 0)
		return ;
	if (move_vec.x != 0)
		update_x(&env->scene, env, (t_v2d_d){move_vec.x, 0});
	if (move_vec.y != 0)
		update_y(&env->scene, env, (t_v2d_d){0, move_vec.y});
}
