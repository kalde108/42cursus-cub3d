#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

#include <math.h>

# include "libft.h"
# include <stdio.h>

static void	portal_hit(t_cubscene *scene, t_ray *ray)
{
	int	portal_id;
	int	dest_portal_id;
	// t_v2d_i	diff;

	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
	dest_portal_id = scene->portals.tab[portal_id].linked_portal;
	if (dest_portal_id != -1)
	{
		// diff.x = scene->portals.tab[dest_portal_id].pos.x - scene->portals.tab[portal_id].pos.x;
		// diff.y = scene->portals.tab[dest_portal_id].pos.y - scene->portals.tab[portal_id].pos.y;
		ray->map_pos = scene->portals.tab[dest_portal_id].pos;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				ray->map_pos.x += 1;
			else
				ray->map_pos.x -= 1;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				ray->map_pos.y += 1;
			else
				ray->map_pos.y -= 1;
		}
		// ray->side_dist.x -= diff.x;
		// ray->side_dist.y -= diff.y;
	}
}

void	ft_dda_fake(t_cubscene *scene, t_ray *ray, t_v2d_d player_pos, t_img *img, int debug)
{
	int	hit;
	// t_v2d_d	ray_hit;
	t_v2d_d	prev;
	t_v2d_d cur;
	double	perp_wall_dist;
	t_v2d_i	jump;
	int		prev_hit;
	int		count;
	t_v2d_i diff;
	int		pid2;

	prev_hit = -1;
	prev = player_pos;
	cur = player_pos;
	hit = 0;
	count = 0;
	jump = (t_v2d_i){0, 0};
	while (hit == 0 && count < 100)
	{
		// if (prev_type == '2')
		// {
		// 	jump = -27.0;
		// 	prev.x -= 27.0;
		// 	prev_type = '\0';
		// }
		// else if (prev_type == '3')
		// {
		// 	jump = 27.0;
		// 	prev.x += 27.0;
		// 	prev_type = '\0';
		// }
		if (prev_hit != -1)
		{
			if (debug)
			{
				dprintf(2, "prev_hit: %d\n", prev_hit);
				dprintf(2, "linked_portal: %d\n", scene->portals.tab[prev_hit].linked_portal);
			}
			// else
			// 	dprintf(2, ".");
			if (prev_hit != 0)
				dprintf(2, "AAAAAAAAAAAAAAAAAAAAAA: %d\n", prev_hit);
			pid2 = scene->portals.tab[prev_hit].linked_portal;
			diff.x = scene->portals.tab[pid2].pos.x - scene->portals.tab[prev_hit].pos.x;
			diff.y = scene->portals.tab[pid2].pos.y - scene->portals.tab[prev_hit].pos.y;
			if (ray->side == 0)
			{
				if (ray->ray_dir.x > 0)
					diff.x += 1;
				else
					diff.x -= 1;
			}
			else if (ray->side == 1)
			{
				if (ray->ray_dir.y > 0)
					diff.y += 1;
				else
					diff.y -= 1;
			}
			prev.x += diff.x;
			prev.y += diff.y;
			jump.x += diff.x;
			jump.y += diff.y;
			prev_hit = -1;
		}
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (IS_WALL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			hit = 1;
			prev_hit = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
		}
		if (IS_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
		{
			// hit = 1;
			ray->hit_type = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
			portal_hit(scene, ray);
			prev_hit = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);

		}
		// else if (scene->map[ray->map_pos.y * scene->width + ray->map_pos.x] == '2')
		// {
		// 	ray->map_pos = (t_v2d_i){1, 9};
		// 	// if (test_flag)
		// 	// {
		// 		// jump = -27.0;
		// 		// prev.x -= 27.0;
		// 	// }
		// 	prev_type = '2';
		// }
		// else if (scene->map[ray->map_pos.y * scene->width + ray->map_pos.x] == '3')
		// {
		// 	ray->map_pos = (t_v2d_i){27, 9};
		// 	// if (test_flag)
		// 	// {
		// 		// jump = 27.0;
		// 		// prev.x += 27.0;
		// 	// }
		// 	prev_type = '3';
		// }
		if (ray->side == 0)
			perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
		else
			perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
		cur.x = player_pos.x + (ray->ray_dir.x) * perp_wall_dist + jump.x;
		cur.y = player_pos.y + (ray->ray_dir.y) * perp_wall_dist + jump.y;
		draw_line(img,
			(int)(prev.x * MINIMAP_SCALE),
			(int)(prev.y * MINIMAP_SCALE),
			(int)(cur.x * MINIMAP_SCALE),
			(int)(cur.y * MINIMAP_SCALE),
			0x007F00);
		prev = cur;
		count++;
	}
}

void	draw_view_cone(t_c3_env *env)
{
	t_ray	ray;
	// t_v2d_d	ray_hit;
	int		x;
	// double	perp_wall_dist;

	x = 0;
	while (x < WIDTH)
	{
		ray_calculation(&env->player, &ray, x);
		// ft_dda(&env->scene, &ray);
		ft_dda_fake(&env->scene, &ray, env->player.pos, &env->img, x == 500);
		// if (ray.side == 0)
		// 	perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
		// else
		// 	perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
		// ray_hit.x = env->player.pos.x + ray.ray_dir.x * perp_wall_dist;
		// ray_hit.y = env->player.pos.y + ray.ray_dir.y * perp_wall_dist;
		// draw_line(&env->img,
		// 	(int)(env->player.pos.x * MINIMAP_SCALE),
		// 	(int)(env->player.pos.y * MINIMAP_SCALE),
		// 	(int)(ray_hit.x * MINIMAP_SCALE),
		// 	(int)(ray_hit.y * MINIMAP_SCALE),
		// 	0x007F00);
		x++;
	}
}
