#include "cub3d.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

# include <math.h>
# include <stdio.h>

void	draw_border(t_c3_env *env)
{
	int	half_size;

	half_size = env->options.minimap.size >> 1;
	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x, env->options.minimap.pos.y - half_size - 2}, (t_v2d_i){env->options.minimap.size + 4, 2}, MINIMAP_BORDER_COLOR);
	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x, env->options.minimap.pos.y + half_size + 1}, (t_v2d_i){env->options.minimap.size + 4, 2}, MINIMAP_BORDER_COLOR);
	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x - half_size - 2, env->options.minimap.pos.y}, (t_v2d_i){2, env->options.minimap.size + 4}, MINIMAP_BORDER_COLOR);
	draw_rectangle(&env->img, (t_v2d_i){env->options.minimap.pos.x + half_size + 1, env->options.minimap.pos.y}, (t_v2d_i){2, env->options.minimap.size + 4}, MINIMAP_BORDER_COLOR);
}

static void	draw_scene(t_c3_env *env, double angle)
{
	int		i;
	int		j;

	t_v2d_d	pos;

	int		cell;
	t_color	color;

	i = -(env->options.minimap.size / 2);
	while (i < env->options.minimap.size / 2)
	{
		j = -(env->options.minimap.size / 2);
		while (j < env->options.minimap.size / 2)
		{
			pos = (t_v2d_d){env->player.camera.pos.x + ((double)j / env->options.minimap.zoom), env->player.camera.pos.y + ((double)i / env->options.minimap.zoom)};
			if (!env->options.minimap.lock)
				ft_rotate_v2_around(&pos, angle, env->player.camera.pos);
			if (pos.x >= 0 && pos.x < env->scene.width && pos.y >= 0 && pos.y < env->scene.height)
			{
				cell = env->scene.map[(int)pos.y * env->scene.width + (int)pos.x];
				color = get_tile_color(env, cell);
				if (cell == EMPTY_CELL)
					put_pixel_alpha(&env->img, j + env->options.minimap.pos.x, i + env->options.minimap.pos.y, color);
				else
					put_pixel(&env->img, j + env->options.minimap.pos.x, i + env->options.minimap.pos.y, color);
			}
			else
				put_pixel_alpha(&env->img, j + env->options.minimap.pos.x, i + env->options.minimap.pos.y, (t_color){0x7F000000});
			j++;
		}
		i++;
	}
}

void	draw_triangle_flat_bottom(t_img *img, t_v2d_i a, t_v2d_i b, t_v2d_i c, t_color color)
{
	double	slope1;
	double	slope2;
	double	x1;
	double	x2;
	int		y;

	slope1 = (double)(b.x - a.x) / (double)(b.y - a.y);
	slope2 = (double)(c.x - a.x) / (double)(c.y - a.y);
	x1 = a.x;
	x2 = a.x;
	y = a.y;
	while (y <= b.y)
	{
		draw_line(img, x1, y, x2, y, color);
		x1 += slope1;
		x2 += slope2;
		y++;
	}
}

void	draw_triangle_flat_top(t_img *img, t_v2d_i a, t_v2d_i b, t_v2d_i c, t_color color)
{
	double	slope1;
	double	slope2;
	double	x1;
	double	x2;
	int		y;

	slope1 = (double)(c.x - a.x) / (double)(c.y - a.y);
	slope2 = (double)(c.x - b.x) / (double)(c.y - b.y);
	x1 = c.x;
	x2 = c.x;
	y = c.y;
	while (y > a.y)
	{
		draw_line(img, x1, y, x2, y, color);
		x1 -= slope1;
		x2 -= slope2;
		y--;
	}
}

void	draw_triangle(t_img *img, t_v2d_i a, t_v2d_i b, t_v2d_i c, t_color color)
{
	t_v2d_i	tmp;

	(void)img;
	(void)color;
	if (a.y == b.y && a.y == c.y)
		return ;
	if (a.y > b.y)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	if (a.y > c.y)
	{
		tmp = a;
		a = c;
		c = tmp;
	}
	if (b.y > c.y)
	{
		tmp = b;
		b = c;
		c = tmp;
	}
	if (b.y == c.y)
	{
		draw_triangle_flat_bottom(img, a, b, c, color);
	}
	else if (a.y == b.y)
	{
		draw_triangle_flat_top(img, a, b, c, color);
	}
	else
	{
		t_v2d_i	d;
		t_v2d_i	e;

		d.x = a.x + (int)((double)(b.y - a.y) / (double)(c.y - a.y) * (c.x - a.x));
		d.y = b.y;
		e = b;
		draw_triangle_flat_bottom(img, a, b, d, color);
		draw_triangle_flat_top(img, b, d, c, color);
	}
	draw_line(img, a.x, a.y, b.x , b.y, color);
	draw_line(img, b.x, b.y, c.x , c.y, color);
	draw_line(img, c.x, c.y, a.x , a.y, color);
}

void	draw_player(t_c3_env *env, double angle)
{
	t_v2d_d	a;
	t_v2d_d	b;
	t_v2d_d	c;
	t_v2d_d	d;

	(void)angle;
	a = (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y - env->options.minimap.zoom / 2};
	b = (t_v2d_d){env->options.minimap.pos.x - env->options.minimap.zoom / 2, env->options.minimap.pos.y + env->options.minimap.zoom / 2};
	c = (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y + env->options.minimap.zoom / 3};
	d = (t_v2d_d){env->options.minimap.pos.x + env->options.minimap.zoom / 2, env->options.minimap.pos.y + env->options.minimap.zoom / 2};
	if (env->options.minimap.lock)
	{
		ft_rotate_v2_around(&a, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
		ft_rotate_v2_around(&b, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
		ft_rotate_v2_around(&c, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
		ft_rotate_v2_around(&d, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
	}
	draw_triangle(&env->img, (t_v2d_i){a.x, a.y}, (t_v2d_i){b.x, b.y}, (t_v2d_i){c.x, c.y}, (t_color){0x65e004});
	draw_triangle(&env->img, (t_v2d_i){a.x, a.y}, (t_v2d_i){c.x, c.y}, (t_v2d_i){d.x, d.y}, (t_color){0x52af08});
}

void	draw_minimap(t_c3_env *env)
{
	double	angle;

	angle = player_angle(env->player.camera.dir);
	draw_scene(env, angle);
	if (env->options.minimap.view)
		draw_view_cone(env, -angle);
	draw_player(env, angle);
}
