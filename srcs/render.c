#include "mlx.h"
#include "cub3d.h"
#include "draw.h"
#include "key_index.h"

static void	update_player(t_c3_env *env)
{
	float	gravity;

	gravity = 0.01;
	env->player.y_speed += gravity;
	if (env->player.y == HEIGHT - 50)
	{
		if (env->key_state[KEY_W] || env->key_state[KEY_SPACE])
			env->player.y_speed = -1.5;
		if (env->key_state[KEY_A])
			env->player.x_speed = -1;
		else if (env->key_state[KEY_D])
			env->player.x_speed = 1;
		else
			env->player.x_speed = 0;
	}

	env->player.y += env->player.y_speed;
	env->player.x += env->player.x_speed;
	if (env->player.y > HEIGHT - 50)
	{
		env->player.y = HEIGHT - 50;
		env->player.y_speed = 0;
	}
}

int	render(t_c3_env *env)
{
	clean_screen(env);
	update_player(env);
	draw_square(env, env->player.x, env->player.y, 100, 0x00FF00);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
