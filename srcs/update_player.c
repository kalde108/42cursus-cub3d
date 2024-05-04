#include "cub3d.h"
#include "key_index.h"

#include <math.h>

# define OFFSET 0.1

static t_v2d_d	get_move_vec(t_c3_env *env)
{
	t_v2d_d	move_vec;

	move_vec = (t_v2d_d){0, 0};
	if (env->key_state[KEY_W])
	{
		move_vec.x += env->player.dir.x * env->player.mv_speed;
		move_vec.y += env->player.dir.y * env->player.mv_speed;
	}
	if (env->key_state[KEY_S])
	{
		move_vec.x -= env->player.dir.x * env->player.mv_speed;
		move_vec.y -= env->player.dir.y * env->player.mv_speed;
	}
	if (env->key_state[KEY_A])
	{
		move_vec.x += env->player.dir.y * env->player.mv_speed;
		move_vec.y -= env->player.dir.x * env->player.mv_speed;
	}
	if (env->key_state[KEY_D])
	{
		move_vec.x -= env->player.dir.y * env->player.mv_speed;
		move_vec.y += env->player.dir.x * env->player.mv_speed;
	}
	return (move_vec);
}

static void	update_pos(t_c3_env *env)
{
	t_v2d_d	move_vec;
	t_v2d_d	offset;

	move_vec = get_move_vec(env);
	offset.x = ((move_vec.x >= 0) - (move_vec.x < 0)) * OFFSET;
	offset.y = ((move_vec.y >= 0) - (move_vec.y < 0)) * OFFSET;
	offset = (t_v2d_d){0, 0}; // remove this line
	if (test_map[(int)env->player.pos.y][(int)(env->player.pos.x + move_vec.x + offset.x)] == '0')
		env->player.pos.x += move_vec.x;
	if (test_map[(int)(env->player.pos.y + move_vec.y + offset.y)][(int)env->player.pos.x] == '0')
		env->player.pos.y += move_vec.y;
}

static void	update_rotation(t_c3_env *env)
{
	double	old_dir_x;
	double	old_plane_x;

	if (env->key_state[KEY_RIGHT])
	{

		old_dir_x = env->player.dir.x;
		env->player.dir.x = env->player.dir.x * cos(env->player.rt_speed) - env->player.dir.y * sin(env->player.rt_speed);
		env->player.dir.y = old_dir_x * sin(env->player.rt_speed) + env->player.dir.y * cos(env->player.rt_speed);
		old_plane_x = env->player.plane.x;
		env->player.plane.x = env->player.plane.x * cos(env->player.rt_speed) - env->player.plane.y * sin(env->player.rt_speed);
		env->player.plane.y = old_plane_x * sin(env->player.rt_speed) + env->player.plane.y * cos(env->player.rt_speed);
	}
	if (env->key_state[KEY_LEFT])
	{
		old_dir_x = env->player.dir.x;
		env->player.dir.x = env->player.dir.x * cos(-env->player.rt_speed) - env->player.dir.y * sin(-env->player.rt_speed);
		env->player.dir.y = old_dir_x * sin(-env->player.rt_speed) + env->player.dir.y * cos(-env->player.rt_speed);
		old_plane_x = env->player.plane.x;
		env->player.plane.x = env->player.plane.x * cos(-env->player.rt_speed) - env->player.plane.y * sin(-env->player.rt_speed);
		env->player.plane.y = old_plane_x * sin(-env->player.rt_speed) + env->player.plane.y * cos(-env->player.rt_speed);
	}
}

void	update_player(t_c3_env *env)
{
	update_pos(env);
	update_rotation(env);
}
