#include "cub3d.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

# include <math.h>
# include <stdio.h>

void	draw_border(t_c3_env *env)
{
	int	half_size;

	half_size = MINIMAP_SIZE >> 1;
	draw_rectangle(&env->img, (t_v2d_i){MINIMAP_X, MINIMAP_Y - half_size - 2}, (t_v2d_i){MINIMAP_SIZE + 4, 2}, MINIMAP_BORDER_COLOR);
	draw_rectangle(&env->img, (t_v2d_i){MINIMAP_X, MINIMAP_Y + half_size + 1}, (t_v2d_i){MINIMAP_SIZE + 4, 2}, MINIMAP_BORDER_COLOR);
	draw_rectangle(&env->img, (t_v2d_i){MINIMAP_X - half_size - 2, MINIMAP_Y}, (t_v2d_i){2, MINIMAP_SIZE + 4}, MINIMAP_BORDER_COLOR);
	draw_rectangle(&env->img, (t_v2d_i){MINIMAP_X + half_size + 1, MINIMAP_Y}, (t_v2d_i){2, MINIMAP_SIZE + 4}, MINIMAP_BORDER_COLOR);
}

void	ft_rotate_v2_around(t_v2d_d *v, double angle, t_v2d_d center)
{
	double	sin_angle;
	double	cos_angle;
	double	old_x;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	old_x = v->x;
	v->x = (v->x - center.x) * cos_angle - (v->y - center.y) * sin_angle + center.x;
	v->y = (old_x - center.x) * sin_angle + (v->y - center.y) * cos_angle + center.y;
}

double	player_angle(t_v2d_d player)
{
	double	magnitude;
	double	cos_angle;
	double	angle;

	magnitude = sqrt(-player.x * -player.x + -player.y * -player.y);
	cos_angle = -player.y / magnitude;
	if (cos_angle > 1.0)
		cos_angle = 1.0;
	if (cos_angle < -1.0)
		cos_angle = -1.0;
	angle = acos(cos_angle);
	if (player.x < 0)
		angle = -angle;
	return angle;
}

double calculate_angle(t_v2d_d player, t_v2d_d origin)
{
	double	dot_product;
	double	magnitude_v1;
	double	magnitude_v2;
	double	cos_angle;
	double	angle;

	dot_product = -player.x * origin.x + -player.y * origin.y;
	magnitude_v1 = sqrt(-player.x * -player.x + -player.y * -player.y);
	magnitude_v2 = sqrt(origin.x * origin.x + origin.y * origin.y);
	cos_angle = dot_product / (magnitude_v1 * magnitude_v2);
	if (cos_angle > 1.0)
		cos_angle = 1.0;
	if (cos_angle < -1.0)
		cos_angle = -1.0;
	angle = acos(cos_angle);
	if (player.x < 0)
		angle = -angle;
	return angle;
}

t_color	get_tile_color(t_c3_env *env, int cell)
{
	t_color	color;

	if (IS_WALL(cell))
		color = env->scene.elems[WALL][GET_WALL(cell)].current->average_color;
	else if (IS_PORTAL(cell))
	{
		if (env->scene.portals.tab[GET_PORTAL(cell)].is_open)
			color = env->scene.elems[PORTAL]->current->average_color;
		else
			color = env->scene.elems[PORTAL]->frames->average_color;
	}
	else if (IS_FL_CE(cell))
		color = env->scene.elems[FLOOR][GET_FLOOR(cell)].current->average_color;
	else
		color.argb = 0x7F000000;
	return color;
}

static void	draw_map(t_c3_env *env)
{
	double	angle;
	int		i;
	int		j;

	t_v2d_d	pos;

	int		cell;
	t_color	color;

	angle = player_angle(env->player.camera.dir);
	i = -(MINIMAP_SIZE / 2);
	while (i < MINIMAP_SIZE / 2)
	{
		j = -(MINIMAP_SIZE / 2);
		while (j < MINIMAP_SIZE / 2)
		{
			pos = (t_v2d_d){env->player.camera.pos.x + ((double)j / MINIMAP_ZOOM), env->player.camera.pos.y + ((double)i / MINIMAP_ZOOM)};
			ft_rotate_v2_around(&pos, angle, env->player.camera.pos);
			if (pos.x >= 0 && pos.x < env->scene.width && pos.y >= 0 && pos.y < env->scene.height)
			{
				cell = env->scene.map[(int)pos.y * env->scene.width + (int)pos.x];
				color = get_tile_color(env, cell);
				if (cell == EMPTY_CELL)
					put_pixel_alpha(&env->img, j + MINIMAP_X, i + MINIMAP_Y, color);
				else
					put_pixel(&env->img, j + MINIMAP_X, i + MINIMAP_Y, color);
			}
			else
				put_pixel_alpha(&env->img, j + MINIMAP_X, i + MINIMAP_Y, (t_color){0x7F000000});
			j++;
		}
		i++;
	}
}

// static void	draw_player(t_c3_env *env)
// {
// 	int		x;
// 	int		y;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < MINIMAP_ZOOM)
// 	{
// 		j = 0;
// 		while (j < MINIMAP_ZOOM)
// 		{
// 			x = (int)(env->player.camera.pos.x * MINIMAP_ZOOM) + j - MINIMAP_ZOOM / 2;
// 			y = (int)(env->player.camera.pos.y * MINIMAP_ZOOM) + i - MINIMAP_ZOOM / 2;
// 			put_pixel(&env->img, x, y, (t_color){0x0000FF00});
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	draw_view(t_c3_env *env)
// {
// 	t_v2d_d	view_end;
// 	int		x;
// 	int		y;

// 	view_end.x = env->player.camera.pos.x + env->player.camera.dir.x * 2.5;
// 	view_end.y = env->player.camera.pos.y + env->player.camera.dir.y * 2.5;
// 	x = (int)(view_end.x * MINIMAP_ZOOM);
// 	y = (int)(view_end.y * MINIMAP_ZOOM);
// 	draw_line_gradient(&env->img, (int)(env->player.camera.pos.x * MINIMAP_ZOOM), (int)(env->player.camera.pos.y * MINIMAP_ZOOM), x, y, (t_color){0x0000FF00}, (t_color){0x00FFFFFF});
// }

// static void	draw_plane(t_c3_env *env)
// {
// 	t_v2d_d	plane_start;
// 	t_v2d_d	plane_end;

// 	plane_start.x = env->player.camera.pos.x + env->player.camera.dir.x * 2.5 - env->player.camera.plane.x * 5 / 2;
// 	plane_start.y = env->player.camera.pos.y + env->player.camera.dir.y * 2.5 - env->player.camera.plane.y * 5 / 2;
// 	plane_end.x = env->player.camera.pos.x + env->player.camera.dir.x * 2.5 + env->player.camera.plane.x * 5 / 2;
// 	plane_end.y = env->player.camera.pos.y + env->player.camera.dir.y * 2.5 + env->player.camera.plane.y * 5 / 2;
// 	draw_line_gradient(&env->img, (int)(plane_start.x * MINIMAP_ZOOM), (int)(plane_start.y * MINIMAP_ZOOM), (int)(plane_end.x * MINIMAP_ZOOM), (int)(plane_end.y * MINIMAP_ZOOM), (t_color){0x000000FF}, (t_color){0x00FFFFFF});
// }

void	draw_minimap(t_c3_env *env)
{
	// draw_border(env);
	draw_map(env);
	// draw_view_cone(env);
	// draw_view(env);
	// draw_plane(env);
	// draw_player(env);
}
