/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/11 19:27:10 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "tile_address.h"

# include <stdio.h>

static inline void	precompute_steps(t_entity *player, t_v2d_d *floor_step, t_v2d_d *floor, size_t y)
{
	t_v2d_d	ray_dir0;
	t_v2d_d	ray_dir1;
	float	row_distance;

	ray_dir0.x = player->dir.x - player->plane.x;
	ray_dir0.y = player->dir.y - player->plane.y;
	ray_dir1.x = player->dir.x + player->plane.x;
	ray_dir1.y = player->dir.y + player->plane.y;
	row_distance = (0.5 * HEIGHT) / (y - (HEIGHT >> 1));
	floor_step->x = row_distance * (ray_dir1.x - ray_dir0.x) / WIDTH;
	floor_step->y = row_distance * (ray_dir1.y - ray_dir0.y) / WIDTH;
	floor->x = player->pos.x + row_distance * ray_dir0.x;
	floor->y = player->pos.y + row_distance * ray_dir0.y;
}

static inline int	get_background_color(t_texdata *texture, t_v2d_d floor, t_v2d_i cell_pos)
{
	t_v2d_i	tex_coord;

	tex_coord.x = (int)(texture->width * (floor.x - cell_pos.x));
	tex_coord.y = (int)(texture->height * (floor.y - cell_pos.y));

	return (((uint32_t *)texture->addr)[texture->width * tex_coord.y + tex_coord.x]);
}

static inline void	background_pixel(t_c3_env *env, t_v2d_d floor, t_v2d_i pixel, t_tex **textures)
{
	t_v2d_i	cell_pos;
	short	cell;

	cell_pos.x = (int)(floor.x);
	cell_pos.y = (int)(floor.y);
	if (cell_pos.x < 0 || cell_pos.x >= env->scene.width || cell_pos.y < 0 || cell_pos.y >= env->scene.height || NOT_FL_CE(env->scene.map[cell_pos.y * env->scene.width + cell_pos.x]))
		return ;
	cell = env->scene.map[cell_pos.y * env->scene.width + cell_pos.x];
	((__uint32_t *)env->img.addr)[pixel.y * WIDTH + pixel.x] = get_background_color(textures[FLOOR][GET_FLOOR(cell)].sprite, floor, cell_pos);
	((__uint32_t *)env->img.addr)[(HEIGHT - pixel.y - 1) * WIDTH + pixel.x] = get_background_color(textures[CEILING][GET_CEILING(cell)].sprite, floor, cell_pos);
}

static inline void	background_row(t_c3_env *env, int y, t_tex **textures)
{
	t_v2d_d floor_step;
	t_v2d_d	floor;
	
	precompute_steps(&env->player, &floor_step, &floor, y);
	
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		// if ((int)floor.x >= 0 && (int)floor.x < env->scene.width && (int)floor.y >= 0 && (int)floor.y < env->scene.height && env->scene.map[(int)floor.y * env->scene.width + (int)floor.x] == '0')
		background_pixel(env, floor, (t_v2d_i){x, y}, textures);
		floor.x += floor_step.x;
		floor.y += floor_step.y;
		x++;
	}
}

static void	draw_backgound(t_c3_env *env)
{
	int		y;

	y = HEIGHT >> 1;
	while (y < HEIGHT)
	{
		background_row(env, y, env->scene.texture);
		y++;
	}
}

void	floor_and_ceiling(t_c3_env *env)
{
	draw_backgound(env);
}
