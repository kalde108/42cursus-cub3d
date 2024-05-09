/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:15 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 18:34:02 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

// static inline void	draw_ceiling(t_c3_env *env)
// {
// 	register int			cursor;
// 	static const int		max = (HEIGHT * (WIDTH >> 2)) >> 1;
// 	__int128_t				*img_ptr;
// 	const __int128_t		color = ((__int128_t)env->scene.ceiling << 96) + \
// 								((__int128_t)env->scene.ceiling << 64) + \
// 								((__int128_t)env->scene.ceiling << 32) + \
// 								((__int128_t)env->scene.ceiling);

// 	img_ptr = (__int128_t *)env->img.addr;
// 	cursor = -1;
// 	while (++cursor < max)
// 	{
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor] = color;
// 	}
// }

// static inline void	draw_floor(t_c3_env *env)
// {
// 	register int			cursor;
// 	static const int		max = (HEIGHT * (WIDTH >> 2));
// 	__int128_t				*img_ptr;
// 	const __int128_t		color = ((__int128_t)env->scene.floor << 96) + \
// 								((__int128_t)env->scene.floor << 64) + \
// 								((__int128_t)env->scene.floor << 32) + \
// 								((__int128_t)env->scene.floor);

// 	img_ptr = (__int128_t *)env->img.addr;
// 	cursor = ((HEIGHT * (WIDTH >> 2)) >> 1) - 1;
// 	while (++cursor < max)
// 	{
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor++] = color;
// 		img_ptr[cursor] = color;
// 	}
// }

static inline void	precompute_steps(t_player *player, t_v2d_d *floor_step, t_v2d_d *floor, size_t y)
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

static inline void	background_pixel(t_c3_env *env, t_v2d_d floor, t_v2d_i pixel, t_tex *textures)
{
	t_v2d_i	cell;
	t_v2d_i	tex_coord;

	cell.x = (int)(floor.x);
	cell.y = (int)(floor.y);

	if (cell.x < 0 || cell.x >= env->scene.width || cell.y < 0 || cell.y >= env->scene.height || ft_ischarset(env->scene.map[cell.y * env->scene.width + cell.x], WALL_CHARSET))
		return ;

	tex_coord.x = (int)(textures[0].width * (floor.x - cell.x)) & (textures[0].width - 1);
	tex_coord.y = (int)(textures[0].height * (floor.y - cell.y)) & (textures[0].height - 1);

	char tile = env->scene.map[cell.y * env->scene.width + cell.x];
	int	ground_type;

	if (tile == '0')
		ground_type = 0;
	else if (tile == 'F')
		ground_type = 1;
	else
		ground_type = 2;

	// ground_type = 0;

	__uint32_t	color = ((uint32_t *)textures[ground_type].addr)[textures[ground_type].width * tex_coord.y + tex_coord.x];
	((__uint32_t *)env->img.addr)[pixel.y * WIDTH + pixel.x] = color;

	int	is_lamp = ((cell.x & 1) == 0 && (cell.y & 1) == 0) + 3;

	// is_lamp = 4;

	color =  ((uint32_t *)textures[is_lamp].addr)[textures[is_lamp].width * tex_coord.y + tex_coord.x];
	((__uint32_t *)env->img.addr)[(HEIGHT - pixel.y - 1) * WIDTH + pixel.x] = color;
}

static inline void	background_row(t_c3_env *env, int y, t_tex *textures)
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
	t_tex				textures[5];

	textures[0] = env->scene.texture[FL1];
	textures[1] = env->scene.texture[FL2];
	textures[2] = env->scene.texture[CA];
	textures[3] = env->scene.texture[CE];
	textures[4] = env->scene.texture[LA];
	y = HEIGHT >> 1;
	while (y < HEIGHT)
	{
		background_row(env, y, textures);
		y++;
	}
}

void	floor_and_ceiling(t_c3_env *env)
{
	// draw_ceiling(env);
	draw_backgound(env);
}
