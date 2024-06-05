#include "cub3d.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

static void	draw_map(t_c3_env *env)
{
	int		i;
	int		j;
	int		x;
	int		y;
	t_color	color;
	char	alpha;

	alpha = 0;
	i = 0;
	while (i < env->scene.height)
	{
		j = 0;
		while (j < env->scene.width)
		{
			alpha = 0;
			if (IS_WALL(env->scene.map[i * env->scene.width + j]))
				color.argb = 0xd72323;
			else if (IS_PORTAL(env->scene.map[i * env->scene.width + j]))
				color.argb = 0x000000FF;
			else if (IS_FL_CE(env->scene.map[i * env->scene.width + j]))
				color.argb = 0xbc8128;
			else
			{
				color.argb = 0x7F000000;
				alpha = 1;
			}
			x = j * MINIMAP_SCALE;
			while (x < (j + 1) * MINIMAP_SCALE)
			{
				y = i * MINIMAP_SCALE;
				while (y < (i + 1) * MINIMAP_SCALE)
				{
					if (alpha)
						put_pixel_alpha(&env->img, x, y, color);
					else
						put_pixel(&env->img, x, y, color);
					y++;
				}
				x++;
			}
			j++;
		}
		i++;
	}
}

static void	draw_player(t_c3_env *env)
{
	int		x;
	int		y;
	int		i;
	int		j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			x = (int)(env->player.camera.pos.x * MINIMAP_SCALE) + j - MINIMAP_SCALE / 2;
			y = (int)(env->player.camera.pos.y * MINIMAP_SCALE) + i - MINIMAP_SCALE / 2;
			put_pixel(&env->img, x, y, (t_color){0x0000FF00});
			j++;
		}
		i++;
	}
}

static void	draw_view(t_c3_env *env)
{
	t_v2d_d	view_end;
	int		x;
	int		y;

	view_end.x = env->player.camera.pos.x + env->player.camera.dir.x * 2.5;
	view_end.y = env->player.camera.pos.y + env->player.camera.dir.y * 2.5;
	x = (int)(view_end.x * MINIMAP_SCALE);
	y = (int)(view_end.y * MINIMAP_SCALE);
	draw_line_gradient(&env->img, (int)(env->player.camera.pos.x * MINIMAP_SCALE), (int)(env->player.camera.pos.y * MINIMAP_SCALE), x, y, (t_color){0x0000FF00}, (t_color){0x00FFFFFF});
}

static void	draw_plane(t_c3_env *env)
{
	t_v2d_d	plane_start;
	t_v2d_d	plane_end;

	plane_start.x = env->player.camera.pos.x + env->player.camera.dir.x * 2.5 - env->player.camera.plane.x * 5 / 2;
	plane_start.y = env->player.camera.pos.y + env->player.camera.dir.y * 2.5 - env->player.camera.plane.y * 5 / 2;
	plane_end.x = env->player.camera.pos.x + env->player.camera.dir.x * 2.5 + env->player.camera.plane.x * 5 / 2;
	plane_end.y = env->player.camera.pos.y + env->player.camera.dir.y * 2.5 + env->player.camera.plane.y * 5 / 2;
	draw_line_gradient(&env->img, (int)(plane_start.x * MINIMAP_SCALE), (int)(plane_start.y * MINIMAP_SCALE), (int)(plane_end.x * MINIMAP_SCALE), (int)(plane_end.y * MINIMAP_SCALE), (t_color){0x000000FF}, (t_color){0x00FFFFFF});
}

void	draw_minimap(t_c3_env *env)
{
	draw_map(env);
	draw_view_cone(env);
	draw_view(env);
	draw_plane(env);
	draw_player(env);
}
