#include "mlx.h"
#include "cub3d.h"
#include "draw.h"
#include "key_index.h"
#include <math.h>

# include <stdio.h>
# include <stdlib.h>

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

int	render(t_c3_env *env)
{
	// printf("render\n");
	clean_screen(env);

	update_pos(env);

	simple_raycasting(env);

	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
