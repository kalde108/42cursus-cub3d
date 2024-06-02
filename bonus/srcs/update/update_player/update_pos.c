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
	move_dir.x = (env->key_state[KEY_W] - env->key_state[KEY_S]) * env->player.camera.dir.x + \
		(env->key_state[KEY_A] - env->key_state[KEY_D]) * env->player.camera.dir.y;
	move_dir.y = (env->key_state[KEY_W] - env->key_state[KEY_S]) * env->player.camera.dir.y - \
		(env->key_state[KEY_A] - env->key_state[KEY_D]) * env->player.camera.dir.x;
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
	double		offset;

	g_debug = 1;	// REMOVE
	rot = 0;
	camera.pos = env->player.camera.pos;
	camera.dir = (t_v2d_d){(move_vec.x >= 0) - (move_vec.x < 0), 0};
	ray = (t_ray){0};
	while (NOT_WALL(ray.hit_type) && !(IS_PORTAL(ray.hit_type) && -1 == scene->portals.tab[GET_PORTAL(ray.hit_type)].linked_portal))
	{
		if (IS_PORTAL(ray.hit_type))
		{
			portal_hit_move(&env->scene, &ray, &camera, &rot);
			rotate_player(&env->player, rot);
			ft_rotate_v2(&move_vec, rot);
		}
		ray_calculation(&camera, &ray);
		ft_dda(scene, &ray);
		dprintf(2, "x ray.perp_wall_dist = %f\n", ray.perp_wall_dist);
		if (IS_PORTAL(ray.hit_type) && NO_LINK != scene->portals.tab[GET_PORTAL(ray.hit_type)].linked_portal)
			offset = PORTAL_OFFSET;
		else
			offset = PLAYER_SIZE;
		if (ray.perp_wall_dist > fabs(move_vec.x) + offset)
		{
			camera.pos.x += move_vec.x;
			camera.pos.y += move_vec.y;
			break ;
		}
		else if (ray.perp_wall_dist > offset)
		{
			camera.pos.x += (ray.perp_wall_dist - offset) * camera.dir.x;
			camera.pos.y += (ray.perp_wall_dist - offset) * camera.dir.y;
			move_vec.x -= (ray.perp_wall_dist - offset) * camera.dir.x;
			move_vec.y -= (ray.perp_wall_dist - offset) * camera.dir.y;
		}
		else
			dprintf(2, "else x ray.perp_wall_dist = %f\n", ray.perp_wall_dist);
	}
	env->player.camera.pos.x = camera.pos.x;
	env->player.camera.pos.y = camera.pos.y;
	g_debug = 0;	// REMOVE
}

static void	update_y(t_cubscene *scene, t_c3_env *env, t_v2d_d move_vec)
{
	t_ray		ray;
	t_camera	camera;
	double		rot;
	double		offset;

	g_debug = 2;	// REMOVE
	rot = 0;
	camera.pos = env->player.camera.pos;
	camera.dir = (t_v2d_d){0, (move_vec.y >= 0) - (move_vec.y < 0)};
	ray = (t_ray){0};
	while (NOT_WALL(ray.hit_type) && !(IS_PORTAL(ray.hit_type) && NO_LINK == scene->portals.tab[GET_PORTAL(ray.hit_type)].linked_portal))
	{
		if (IS_PORTAL(ray.hit_type))
		{
			portal_hit_move(&env->scene, &ray, &camera, &rot);
			rotate_player(&env->player, rot);
			ft_rotate_v2(&move_vec, rot);
		}
		dprintf(2, "camera.pos.x = %f\tcamera.pos.y = %f\n", camera.pos.x, camera.pos.y);
		ray_calculation(&camera, &ray);
		ft_dda(scene, &ray);
		dprintf(2, "y ray.perp_wall_dist = %f\n", ray.perp_wall_dist);
		if (IS_PORTAL(ray.hit_type) && NO_LINK != scene->portals.tab[GET_PORTAL(ray.hit_type)].linked_portal)
			offset = PORTAL_OFFSET;
		else
			offset = PLAYER_SIZE;
		if (ray.perp_wall_dist > fabs(move_vec.y) + offset)
		{
			camera.pos.x += move_vec.x;
			camera.pos.y += move_vec.y;
			break ;
		}
		else if (ray.perp_wall_dist > offset)	// TODO: check if this is correct
		{
			camera.pos.x += (ray.perp_wall_dist - offset) * camera.dir.x;
			camera.pos.y += (ray.perp_wall_dist - offset) * camera.dir.y;
			move_vec.x -= (ray.perp_wall_dist - offset) * camera.dir.x;
			move_vec.y -= (ray.perp_wall_dist - offset) * camera.dir.y;
		}
		else
			dprintf(2, "else y ray.perp_wall_dist = %f\n", ray.perp_wall_dist);
	}
	env->player.camera.pos.y = camera.pos.y;
	env->player.camera.pos.x = camera.pos.x;
	g_debug = 0;	// REMOVE
}

void	update_pos(t_c3_env *env)
{
	t_v2d_d	move_vec;
	double	move_goal;

	move_vec = get_move_vec(env);
	move_goal = sqrt(move_vec.x * move_vec.x + move_vec.y * move_vec.y);
	if (move_goal == 0)
		return ;
	dprintf(2, "\nupdate_pos\n");
	if (move_vec.x != 0)
		update_x(&env->scene, env, (t_v2d_d){move_vec.x, 0});
	if (move_vec.y != 0)
		update_y(&env->scene, env, (t_v2d_d){0, move_vec.y});
}
