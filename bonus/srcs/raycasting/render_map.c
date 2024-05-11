/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 18:20:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "tile_address.h"

# include <stdio.h>

void	render_map(t_c3_env *env)
{
	t_ray	ray;
	t_vline	line;
	t_texdata	*texture;
	int		tex_x;

	line.x = 0;
	while (line.x < WIDTH)
	{
		ray_calculation(&env->player, &ray, line.x);
		ft_dda(&env->scene, &ray);
		texture = get_wall_texture(&env->scene, ray.map_pos, env->scene.texture);
		// texture = env->scene.texture[WALL][GET_WALL(env->scene.map[ray.map_pos.y * env->scene.width + ray.map_pos.x])];
		dprintf(2, "texture_path: %s\n", texture->filepath);
		dprintf(2, "texture addr: %p\n", texture->addr);
		tex_x = get_tex_x(&ray, texture->width, env->player);
		get_line_y(&line, ray.perp_wall_dist);
		draw_v_line(&env->img, &line, tex_x, texture);
		line.x++;
	}
}
