/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_cone_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:49:24 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:49:24 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minimap.h"

static void	put_dot(t_c3_env *env, t_v2d_d pos, t_color color)
{
	int	dot_size;

	dot_size = 0.1 * env->options.minimap.zoom + 1.0;
	if (is_on_minimap(&env->options.minimap, (int)(pos.x), (int)(pos.y)))
		draw_rectangle(&env->img,
			(t_v2d_i){(int)(pos.x),
			(int)(pos.y)},
			(t_v2d_i){dot_size, dot_size},
			color);
}

static t_v2d_d	get_line_start(t_c3_env *env,
								t_ray *ray,
								t_hit_buffer *buf,
								double prev_z)
{
	t_v2d_d	line_start;
	double	angle;

	line_start.x = ((buf->camera.pos.x + ray->ray_dir.x * prev_z)
			- env->player.camera.pos.x) * env->options.minimap.zoom
		+ env->options.minimap.pos.x;
	line_start.y = ((buf->camera.pos.y + ray->ray_dir.y * prev_z)
			- env->player.camera.pos.y) * env->options.minimap.zoom
		+ env->options.minimap.pos.y;
	if (!env->options.minimap.lock)
	{
		angle = player_angle(env->player.camera.dir);
		ft_rotate_v2_around(&line_start, -angle,
			(t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
	}
	return (line_start);
}

static t_v2d_d	get_ray_hit(t_c3_env *env, t_ray *ray, t_hit_buffer *buf)
{
	t_v2d_d	ray_hit;
	double	angle;

	ray_hit.x = ((buf->camera.pos.x + ray->ray_dir.x * buf->z)
			- env->player.camera.pos.x) * env->options.minimap.zoom
		+ env->options.minimap.pos.x;
	ray_hit.y = ((buf->camera.pos.y + ray->ray_dir.y * buf->z)
			- env->player.camera.pos.y) * env->options.minimap.zoom
		+ env->options.minimap.pos.y;
	if (!env->options.minimap.lock)
	{
		angle = player_angle(env->player.camera.dir);
		ft_rotate_v2_around(&ray_hit, -angle,
			(t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
	}
	return (ray_hit);
}

static t_v2d_d	get_new_camera_pos(t_c3_env *env, t_hit_buffer *buf)
{
	t_v2d_d	new_camera_pos;
	double	angle;

	new_camera_pos.x = ((buf->camera.pos.x - env->player.camera.pos.x)
			* env->options.minimap.zoom + env->options.minimap.pos.x);
	new_camera_pos.y = ((buf->camera.pos.y - env->player.camera.pos.y)
			* env->options.minimap.zoom + env->options.minimap.pos.y);
	if (!env->options.minimap.lock)
	{
		angle = player_angle(env->player.camera.dir);
		ft_rotate_v2_around(&new_camera_pos, -angle,
			(t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
	}
	return (new_camera_pos);
}

void	view_cone_x(t_c3_env *env,
						int x,
						int hit_count,
						t_hit_buffer *hit_buf)
{
	double			prev_z;
	t_ray			ray;
	int				i;
	t_v2d_d			line_start;
	t_v2d_d			ray_hit;

	ray = (t_ray){0};
	prev_z = 0;
	i = 0;
	while (i < hit_count)
	{
		screen_ray_calculation(&hit_buf->camera, &ray, x);
		line_start = get_line_start(env, &ray, hit_buf, prev_z);
		ray_hit = get_ray_hit(env, &ray, hit_buf);
		hit_buf->camera.pos = get_new_camera_pos(env, hit_buf);
		draw_line_minimap(env, (t_v2d_i){line_start.x, line_start.y},
			(t_v2d_i){ray_hit.x, ray_hit.y}, (t_color){0x007F00});
		put_dot(env, hit_buf->camera.pos, (t_color){0xffffff});
		put_dot(env, line_start, (t_color){0xff7eeb});
		put_dot(env, ray_hit, (t_color){0x11d280});
		prev_z = hit_buf->z;
		hit_buf++;
		i++;
	}
}
