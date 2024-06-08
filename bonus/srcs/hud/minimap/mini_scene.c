#include "cub3d.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

static void	scene_pixel(t_c3_env *env, double angle, int i, int j)
{
	t_v2d_d	pos;
	int		cell;
	t_color	color;

	pos.x = env->player.camera.pos.x + (double)j / env->options.minimap.zoom;
	pos.y = env->player.camera.pos.y + (double)i / env->options.minimap.zoom;
	if (!env->options.minimap.lock)
		ft_rotate_v2_around(&pos, angle, env->player.camera.pos);
	if (pos.x >= 0 && pos.x < env->scene.width
		&& pos.y >= 0 && pos.y < env->scene.height)
	{
		cell = env->scene.map[(int)pos.y * env->scene.width + (int)pos.x];
		color = get_tile_color(env, cell);
		if (cell == EMPTY_CELL)
			put_pixel_alpha(&env->img, j + env->options.minimap.pos.x,
				i + env->options.minimap.pos.y, color);
		else
			put_pixel(&env->img, j + env->options.minimap.pos.x,
				i + env->options.minimap.pos.y, color);
	}
	else
		put_pixel_alpha(&env->img, j + env->options.minimap.pos.x,
			i + env->options.minimap.pos.y, (t_color){MINI_BACKGROUND});
}

void	mini_scene(t_c3_env *env, double angle)
{
	int		i;
	int		j;

	i = -(env->options.minimap.size / 2);
	while (i < env->options.minimap.size / 2)
	{
		j = -(env->options.minimap.size / 2);
		while (j < env->options.minimap.size / 2)
		{
			scene_pixel(env, angle, i, j);
			j++;
		}
		i++;
	}
}
