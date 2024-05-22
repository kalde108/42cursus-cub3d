/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/22 20:35:36 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "raycasting.h"
#include "tile_address.h"

# include <stdio.h>
# include <math.h>
# include "ft_math.h"

static int	get_relative_position(int f1, int f2)
{
	int	diff;
	int	relative_position;

	diff = (f2 - f1) % 4;
	relative_position = (diff + 4) % 4;
	return (relative_position);
}

// static void	delta_dist_init(t_ray *ray)
// {
// 	if (ray->ray_dir.x == 0)
// 		ray->delta_dist.x = 1e30;
// 	else
// 		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
// 	if (ray->ray_dir.y == 0)
// 		ray->delta_dist.y = 1e30;
// 	else
// 		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
// }

// static void	step_init(t_v2d_d *pos, t_ray *ray)
// {
// 	if (ray->ray_dir.x < 0)
// 	{
// 		ray->step.x = -1;
// 		ray->side_dist.x = (pos->x - ray->map_pos.x) \
// 							* ray->delta_dist.x;
// 	}
// 	else
// 	{
// 		ray->step.x = 1;
// 		ray->side_dist.x = (ray->map_pos.x + 1.0 - pos->x) \
// 							* ray->delta_dist.x;
// 	}
// 	if (ray->ray_dir.y < 0)
// 	{
// 		ray->step.y = -1;
// 		ray->side_dist.y = (pos->y - ray->map_pos.y) \
// 							* ray->delta_dist.y;
// 	}
// 	else
// 	{
// 		ray->step.y = 1;
// 		ray->side_dist.y = (ray->map_pos.y + 1.0 - pos->y) \
// 							* ray->delta_dist.y;
// 	}
// }

static void	apply_rotation(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(angle) \
						- player->dir.y * sin(angle);
	player->dir.y = old_dir_x * sin(angle) + player->dir.y * cos(angle);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(angle) \
							- player->plane.y * sin(angle);
	player->plane.y = old_plane_x * sin(angle) + \
							player->plane.y * cos(angle);
}

static void	portal_hit(t_cubscene *scene, t_ray *ray, t_player *player)
{
	int	portal_id;
	int	dest_portal_id;
	int	relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

	(void)player;
	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
	portals = scene->portals.tab;
	if (portals[portal_id].is_open == 0)
		return ;	// portal is closed
	dest_portal_id = portals[portal_id].linked_portal;
	// ray->map_pos = scene->portals.tab[dest_portal_id].pos;
	diff.x = (portals[portal_id].pos.x + 0.5) - player->pos.x;
	diff.y = (portals[portal_id].pos.y + 0.5) - player->pos.y;
	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
	if (relative_position == 0)	// same face
	{
	}
	else if (relative_position == 1)	// left face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff = (t_v2d_d){-diff.y, diff.x};
		apply_rotation(player, -PI_2);
		player->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		player->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		// ray->total_perp_wall_dist = -diff.y;
		ray->turn = 1;
	}
	else if (relative_position == 2)	// opposite face
	{
	}
	else if (relative_position == 3)	// right face
	{
	}
}

void	render_map_chunk(t_c3_env *env, int start, int end)
{
	t_ray	ray;
	// t_vline	line;
	// t_texdata	*texture;
	// int		tex_x;
	int				x;
	t_hit_buffer	buffer[MAX_LAYERS];
	int				hit_count;
	// double	total_perp_wall_dist;
	t_player	tmp;

	x = start;
	while (x < end)
	{
		hit_count = 0;
		// total_perp_wall_dist = 0;
		ray.total_perp_wall_dist = 0;
		ray.hit_type = 0;
		tmp = env->player;
		while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
		{
			if (IS_PORTAL(ray.hit_type))
				portal_hit(&env->scene, &ray, &tmp);
			ray_calculation(&tmp, &ray, x);
			ft_dda(&env->scene, &ray, &tmp);
			// if (!hit_count)
				env->z_buffer[x] = ray.perp_wall_dist;
			// if (NOT_WALL(ray.hit_type) && NOT_PORTAL(ray.hit_type))
			// 	dprintf(2, "No hit?: %d\n", ray.hit_type);
			buffer[hit_count].texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
			buffer[hit_count].tex_x = get_tex_x(&ray, buffer[hit_count].texture->width, tmp);
			get_line_y(buffer + hit_count, ray.perp_wall_dist);
			buffer[hit_count].side = ray.side;
			buffer[hit_count].cell = ray.hit_type;
			
			hit_count++;
			// draw_v_line(&env->img, &line, tex_x, texture, &ray);
		}
		while (hit_count-- > 0)
		{
			if (IS_WALL(buffer[hit_count].cell))
				draw_wall(&env->img, buffer + hit_count, x);
			else if (IS_PORTAL(buffer[hit_count].cell))
				draw_portal(&env->img, buffer + hit_count, x);
		}
		
		x++;
	}
}

void	*render_map_thread(void *arg)
{
	static int	call = 0;
	t_c3_env	*env;
	int			start;
	int			end;

	env = (t_c3_env *)arg;
	pthread_mutex_lock(&env->call_mutex);
	call++;
	call = call % CPUCORES;
	start = call * (WIDTH / CPUCORES);
	end = (call + 1) * (WIDTH / CPUCORES);
	pthread_mutex_unlock(&env->call_mutex);
	render_map_chunk(env, start, end);
	return (NULL);
}

int	render_map(t_c3_env *env)
{
	pthread_t	threads[CPUCORES];
	int			i;
	int			err;

	err = 0;
	i = 0;
	while (i < CPUCORES)
	{
		err = pthread_create(&threads[i], NULL, render_map_thread, env);
		if (err)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	return (err);
}
