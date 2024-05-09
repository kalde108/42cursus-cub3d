/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 14:20:46 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	simple_raycasting(t_c3_env *env)
{
	t_ray	ray;
	t_vline	line;
	t_tex	texture;
	int		tex_x;

	line.x = 0;
	while (line.x < WIDTH)
	{
		ray_calculation(&env->player, &ray, line.x);
		ft_dda(&env->scene, &ray);
		texture = get_wall_texture(&env->scene, ray.map_pos, env->scene.texture);
		tex_x = get_tex_x(&ray, texture.width, env->player);
		get_line_y(&line, ray.perp_wall_dist);
		draw_v_line(&env->img, &line, tex_x, &texture);
		line.x++;
	}
}
