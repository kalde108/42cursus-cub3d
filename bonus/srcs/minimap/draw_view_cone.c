#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

#include <math.h>

# include "libft.h"
# include <stdio.h>

// static int	get_relative_position(int f1, int f2)
// {
// 	int	diff;
// 	int	relative_position;

// 	diff = (f2 - f1) % 4;
// 	relative_position = (diff + 4) % 4;
// 	return (relative_position);
// }

// static void	portal_hit(t_cubscene *scene, t_ray *ray)
// {
// 	int	portal_id;
// 	int	dest_portal_id;
// 	int	relative_position;
// 	t_portal	*portals;
// 	int	tmp;

// 	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
// 	portals = scene->portals.tab;
// 	if (portals[portal_id].is_open == 0)
// 		return ;	// portal is closed
// 	dest_portal_id = portals[portal_id].linked_portal;
// 	ray->map_pos = scene->portals.tab[dest_portal_id].pos;
// 	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
// 	if (relative_position == 0)	// same face
// 	{
// 		if (ray->side == 0)
// 		{
// 			ray->step.x = -ray->step.x;
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.x -= 1;
// 			else
// 				ray->map_pos.x += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			ray->step.y = -ray->step.y;
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.y -= 1;
// 			else
// 				ray->map_pos.y += 1;
// 		}
// 	}
// 	else if (relative_position == 1)	// left face
// 	{
// 		tmp = ray->step.x;
// 		ray->step.x = ray->step.y;
// 		ray->step.y = -tmp;
// 		// tmp = ray->ray_dir.x;
// 		// ray->ray_dir.x = ray->ray_dir.y;
// 		// ray->ray_dir.y = -tmp;
// 		// tmp = ray->delta_dist.x;
// 		// ray->delta_dist.x = ray->delta_dist.y;
// 		// ray->delta_dist.y = tmp;
// 		// tmp = ray->side_dist.x;
// 		// ray->side_dist.x = ray->side_dist.y;
// 		// ray->side_dist.y = -tmp;
// 		// ray->map_pos.x -= 1;
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 			// if (ray->ray_dir.x > 0)
// 			// 	ray->map_pos.y -= 1;
// 			// else
// 			// 	ray->map_pos.y += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 		}
// 		// ray->turn = 1;
// 	}
// 	else if (relative_position == 2)	// opposite face
// 	{
// 		// vector stays the same
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.y += 1;
// 			else
// 				ray->map_pos.y -= 1;
// 		}
// 	}
// 	else if (relative_position == 3)	// right face
// 	{
// 		tmp = ray->step.x;
// 		ray->step.x = -ray->step.y;
// 		ray->step.y = tmp;
// 	}

// 	// if (ray->side == 0)
// 	// {
// 	// 	if (ray->ray_dir.x > 0)
// 	// 		ray->map_pos.x += 1;
// 	// 	else
// 	// 		ray->map_pos.x -= 1;
// 	// }
// 	// else if (ray->side == 1)
// 	// {
// 	// 	if (ray->ray_dir.y > 0)
// 	// 		ray->map_pos.y += 1;
// 	// 	else
// 	// 		ray->map_pos.y -= 1;
// 	// }
// }

// void	ft_dda_fake(t_cubscene *scene, t_ray *ray, t_v2d_d player_pos, t_img *img)
// {
// 	int	hit;
// 	// t_v2d_d	ray_hit;
// 	t_v2d_d	prev;
// 	t_v2d_d cur;
// 	double	perp_wall_dist;
// 	t_v2d_i	jump;
// 	int		prev_hit;
// 	int		count;
// 	t_v2d_i diff;
// 	int		pid2;

// 	prev_hit = -1;
// 	prev = player_pos;
// 	cur = player_pos;
// 	hit = 0;
// 	count = 0;
// 	jump = (t_v2d_i){0, 0};
// 	while (hit == 0 && count < 100)
// 	{
// 		// drpintf(2, "count: %d\n", count);
// 		// if (prev_hit != -1)
// 		// {
// 		// 	(void)debug;
// 		// 	// if (debug)
// 		// 	// {
// 		// 	// 	dprintf(2, "prev_hit: %d\n", prev_hit);
// 		// 	// 	dprintf(2, "linked_portal: %d\n", scene->portals.tab[prev_hit].linked_portal);
// 		// 	// }
// 		// 	// // else
// 		// 	// // 	dprintf(2, ".");
// 		// 	// if (prev_hit != 0)
// 		// 	// 	dprintf(2, "AAAAAAAAAAAAAAAAAAAAAA: %d\n", prev_hit);
// 		// 	pid2 = scene->portals.tab[prev_hit].linked_portal;
// 		// 	diff.x = scene->portals.tab[pid2].pos.x - scene->portals.tab[prev_hit].pos.x;
// 		// 	diff.y = scene->portals.tab[pid2].pos.y - scene->portals.tab[prev_hit].pos.y;
// 		// 	// if (ray->side == 0)
// 		// 	// {
// 		// 	// 	if (ray->ray_dir.x > 0)
// 		// 	// 		diff.x += 1;
// 		// 	// 	else
// 		// 	// 		diff.x -= 1;
// 		// 	// }
// 		// 	// else if (ray->side == 1)
// 		// 	// {
// 		// 	// 	if (ray->ray_dir.y > 0)
// 		// 	// 		diff.y += 1;
// 		// 	// 	else
// 		// 	// 		diff.y -= 1;
// 		// 	// }
// 		// 	// diff.x -= 1;
// 		// 	if (ray->side == 0)
// 		// 	{
// 		// 		if (ray->ray_dir.y > 0)
// 		// 			diff.y += 1;
// 		// 		else
// 		// 			diff.y -= 1;
// 		// 		// if (ray->ray_dir.x > 0)
// 		// 		// 	ray->map_pos.y -= 1;
// 		// 		// else
// 		// 		// 	ray->map_pos.y += 1;
// 		// 	}
// 		// 	else if (ray->side == 1)
// 		// 	{
// 		// 		if (ray->ray_dir.y > 0)
// 		// 			diff.x += 1;
// 		// 		else
// 		// 			diff.x -= 1;
// 		// 	}
// 		// 	prev.x += diff.x;
// 		// 	prev.y += diff.y;
// 		// 	jump.x += diff.x;
// 		// 	jump.y += diff.y;
// 		// 	prev_hit = -1;
// 		// }
// 		if (ray->side_dist.x < ray->side_dist.y)
// 		{
// 			ray->side_dist.x += ray->delta_dist.x;
// 			ray->map_pos.x += ray->step.x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist.y += ray->delta_dist.y;
// 			ray->map_pos.y += ray->step.y;
// 			ray->side = 1;
// 		}
// 		if (IS_WALL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
// 		{
// 			hit = 1;
// 			prev_hit = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
// 		}
// 		if (IS_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
// 		{
// 			// hit = 1;
// 			ray->hit_type = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
// 			prev_hit = GET_PORTAL(ray->hit_type);
// 			portal_hit(scene, ray);

// 		}
// 		// else if (scene->map[ray->map_pos.y * scene->width + ray->map_pos.x] == '2')
// 		// {
// 		// 	ray->map_pos = (t_v2d_i){1, 9};
// 		// 	// if (test_flag)
// 		// 	// {
// 		// 		// jump = -27.0;
// 		// 		// prev.x -= 27.0;
// 		// 	// }
// 		// 	prev_type = '2';
// 		// }
// 		// else if (scene->map[ray->map_pos.y * scene->width + ray->map_pos.x] == '3')
// 		// {
// 		// 	ray->map_pos = (t_v2d_i){27, 9};
// 		// 	// if (test_flag)
// 		// 	// {
// 		// 		// jump = 27.0;
// 		// 		// prev.x += 27.0;
// 		// 	// }
// 		// 	prev_type = '3';
// 		// }
// 		if (ray->side == 0)
// 			perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
// 		else
// 			perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
// 		cur.x = player_pos.x + (ray->ray_dir.x) * perp_wall_dist + jump.x;
// 		cur.y = player_pos.y + (ray->ray_dir.y) * perp_wall_dist + jump.y;
// 		draw_line(img,
// 			(int)(prev.x * MINIMAP_SCALE),
// 			(int)(prev.y * MINIMAP_SCALE),
// 			(int)(cur.x * MINIMAP_SCALE),
// 			(int)(cur.y * MINIMAP_SCALE),
// 			0x007F00);
// 		prev = cur;
// 		count++;
// 	}
// }

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

// static void	portal_hit(t_cubscene *scene, t_ray *ray, t_v2d_d *prev_start, t_player *player)
// {
// 	int	portal_id;
// 	int	dest_portal_id;
// 	int	relative_position;
// 	t_portal	*portals;
// 	t_v2d_d		diff;
// 	double	tmp1;
// 	t_v2d_d	tmp3;

// 	portals = scene->portals.tab;
// 	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
// 	if (portals[portal_id].is_open == 0)
// 		return ;	// portal is closed
// 	dest_portal_id = portals[portal_id].linked_portal;
// 	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
// 	diff.x = scene->portals.tab[dest_portal_id].pos.x - scene->portals.tab[portal_id].pos.x;
// 	diff.y = scene->portals.tab[dest_portal_id].pos.y - scene->portals.tab[portal_id].pos.y;
// 	if (relative_position == 0)	// same face
// 	{
// 		// no change
// 	}
// 	else if (relative_position == 1)	// left face
// 	{
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				diff.y -= 1;
// 			else
// 				diff.y += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				diff.x += 1;
// 			else
// 				diff.x -= 1;
// 		}
// 	}
// 	else if (relative_position == 2)	// opposite face
// 	{
// 		// vector stays the same
// 		tmp1 = ray->ray_dir.x;
// 		ray->ray_dir.x = ray->ray_dir.y;
// 		ray->ray_dir.y = -tmp1;
// 		delta_dist_init(ray);
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				diff.x += 1;
// 			else
// 				diff.x -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				diff.y += 1;
// 			else
// 				diff.y -= 1;
// 		}
// 		tmp3.x = ray->map_pos.x + (player->pos.x - floor(player->pos.x));
// 		tmp3.y = ray->map_pos.y + (player->pos.y - floor(player->pos.y));
// 		step_init(&tmp3, ray);
// 	}
// 	else if (relative_position == 3)	// right face
// 	{
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				diff.y += 1;
// 			else
// 				diff.y -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				diff.x -= 1;
// 			else
// 				diff.x += 1;
// 		}
// 	}
// 	prev_start->x += diff.x;
// 	prev_start->y += diff.y;
// }

// static void	apply_rotation(t_player *player, double angle)
// {
// 	double	old_dir_x;
// 	double	old_plane_x;

// 	old_dir_x = player->dir.x;
// 	player->dir.x = player->dir.x * cos(angle) \
// 						- player->dir.y * sin(angle);
// 	player->dir.y = old_dir_x * sin(angle) + player->dir.y * cos(angle);
// 	old_plane_x = player->plane.x;
// 	player->plane.x = player->plane.x * cos(angle) \
// 							- player->plane.y * sin(angle);
// 	player->plane.y = old_plane_x * sin(angle) + \
// 							player->plane.y * cos(angle);
// }

// static void	portal_hit(t_cubscene *scene, t_ray *ray, t_player *player)
// {
// 	int	portal_id;
// 	int	dest_portal_id;
// 	int	relative_position;
// 	t_portal	*portals;
// 	t_v2d_d		diff;

// 	(void)player;
// 	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
// 	portals = scene->portals.tab;
// 	if (portals[portal_id].is_open == 0)
// 		return ;	// portal is closed
// 	dest_portal_id = portals[portal_id].linked_portal;
// 	// ray->map_pos = scene->portals.tab[dest_portal_id].pos;
// 	diff.x = (portals[portal_id].pos.x + 0.5) - player->pos.x;
// 	diff.y = (portals[portal_id].pos.y + 0.5) - player->pos.y;
// 	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
// 	if (relative_position == 0)	// same face
// 	{
// 	}
// 	else if (relative_position == 1)	// left face
// 	{
// 		// rotate vector (diff) 90 degrees relative to the portal
// 		diff = (t_v2d_d){diff.y, -diff.x};
// 		apply_rotation(player, -PI_2);
// 	}
// 	else if (relative_position == 2)	// opposite face
// 	{
// 	}
// 	else if (relative_position == 3)	// right face
// 	{
// 	}
// 	player->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
// 	player->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
// }

void	draw_view_cone(t_c3_env *env)
{
	(void)env;
		// t_ray	ray;
		// t_v2d_d	ray_hit;
		// int		x;
		// int		hit_count;
		// t_v2d_d	prev_start;
		// double	total_perp_wall_dist;
		// t_v2d_i tmp;
		// t_player	tmp_player;

		// x = 0;
		// while (x < WIDTH)
		// {
		// 	prev_start = env->player.pos;
		// 	hit_count = 0;
		// 	ray.hit_type = 0;
		// 	total_perp_wall_dist = 0;
		// 	ray_calculation(&env->player, &ray, x);
		// 	while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
		// 	{
		// 		if (IS_PORTAL(ray.hit_type))
		// 		{
		// 			portal_hit(&env->scene, &ray, &prev_start, &env->player);
		// 		}
		// 		ft_dda(&env->scene, &ray, &env->player);
		// 		// if (!hit_count)
		// 			// env->z_buffer[x] = ray.perp_wall_dist;
		// 		// if (NOT_WALL(ray.hit_type) && NOT_PORTAL(ray.hit_type))
		// 		// 	dprintf(2, "No hit?: %d\n", ray.hit_type);
		// 		// buffer[hit_count].texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
		// 		// buffer[hit_count].tex_x = get_tex_x(&ray, buffer[hit_count].texture->width, env->player);
		// 		// get_line_y(buffer + hit_count, ray.perp_wall_dist);
		// 		// buffer[hit_count].side = ray.side;
		// 		// buffer[hit_count].cell = ray.hit_type;
		// 		ray_hit.x = prev_start.x + ray.ray_dir.x * (ray.perp_wall_dist - total_perp_wall_dist);
		// 		ray_hit.y = prev_start.y + ray.ray_dir.y * (ray.perp_wall_dist - total_perp_wall_dist);
		// 		total_perp_wall_dist = ray.perp_wall_dist;
		// 		// draw_line(&env->img,
		// 		// 	(int)(prev_start.x * MINIMAP_SCALE),
		// 		// 	(int)(prev_start.y * MINIMAP_SCALE),
		// 		// 	(int)(ray_hit.x * MINIMAP_SCALE),
		// 		// 	(int)(ray_hit.y * MINIMAP_SCALE),
		// 		// 	0x007F00);
		// 		tmp = (t_v2d_i){(int)(prev_start.x * MINIMAP_SCALE), (int)(prev_start.y * MINIMAP_SCALE)};
		// 		draw_rectangle(&env->img, tmp, (t_v2d_i){2, 2}, 0xff7eeb);
		// 		tmp = (t_v2d_i){(int)(ray_hit.x * MINIMAP_SCALE), (int)(ray_hit.y * MINIMAP_SCALE)};
		// 		draw_rectangle(&env->img, tmp, (t_v2d_i){2, 2}, 0x11d280);
		// 		prev_start = ray_hit;
		// 		hit_count++;
		// 	}
		// 	// ft_dda_fake(&env->scene, &ray, env->player.pos, &env->img);
		// 	x++;
		// }
}
