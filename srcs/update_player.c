#include "cub3d.h"
#include "key_index.h"

#include <math.h>

static t_v2d_d	get_move_vec(t_c3_env *env)
{
	t_v2d_d	move_vec;

	move_vec = (t_v2d_d){0, 0};
	if (env->key_state[KEY_W])
	{
		move_vec.x += env->dir.x * env->move_speed;
		move_vec.y += env->dir.y * env->move_speed;
	}
	if (env->key_state[KEY_S])
	{
		move_vec.x -= env->dir.x * env->move_speed;
		move_vec.y -= env->dir.y * env->move_speed;
	}
	if (env->key_state[KEY_A])
	{
		move_vec.x -= env->dir.y * env->move_speed;
		move_vec.y += env->dir.x * env->move_speed;
	}
	if (env->key_state[KEY_D])
	{
		move_vec.x += env->dir.y * env->move_speed;
		move_vec.y -= env->dir.x * env->move_speed;
	}
	return (move_vec);
}

static void	update_pos(t_c3_env *env)
{
	t_v2d_d	move_vec;

	move_vec = get_move_vec(env);
	if (test_map[(int)(env->pos.x + move_vec.x)][(int)env->pos.y] == 0)
		env->pos.x += move_vec.x;
	if (test_map[(int)env->pos.x][(int)(env->pos.y + move_vec.y)] == 0)
		env->pos.y += move_vec.y;
}

static void	update_rotation(t_c3_env *env)
{
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

void	update_player(t_c3_env *env)
{
	update_pos(env);
	update_rotation(env);
}
