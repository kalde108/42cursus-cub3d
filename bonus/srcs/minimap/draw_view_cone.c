#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

#include <math.h>

# include "libft.h"
# include <stdio.h>

static int	get_relative_position(int f1, int f2)
{
	int	diff;
	int	relative_position;

	diff = (f2 - f1) % 4;
	relative_position = (diff + 4) % 4;
	return (relative_position);
}

static void	apply_rotation(t_camera *camera, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = camera->dir.x;
	camera->dir.x = camera->dir.x * cos(angle) \
						- camera->dir.y * sin(angle);
	camera->dir.y = old_dir_x * sin(angle) + camera->dir.y * cos(angle);
	old_plane_x = camera->plane.x;
	camera->plane.x = camera->plane.x * cos(angle) \
							- camera->plane.y * sin(angle);
	camera->plane.y = old_plane_x * sin(angle) + \
							camera->plane.y * cos(angle);
}

static void	fake_portal_hit(t_cubscene *scene, t_ray *ray, t_camera *camera)
{
	int	portal_id;
	int	dest_portal_id;
	int	relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

	(void)camera;
	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
	portals = scene->portals.tab;
	if (portals[portal_id].is_open == 0)
		return ;	// portal is closed
	dest_portal_id = portals[portal_id].linked_portal;
	diff.x = (portals[portal_id].pos.x + 0.5) - camera->pos.x;
	diff.y = (portals[portal_id].pos.y + 0.5) - camera->pos.y;
	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
	if (relative_position == 0)	// same face
	{
		// rotate vector (diff) 180 degrees relative to the portal
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		apply_rotation(camera, PI);
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.x -= 0.999999999;
			else
				camera->pos.x += 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.y -= 0.999999999;
			else
				camera->pos.y += 0.999999999;
		}
	}
	else if (relative_position == 1)	// left face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff = (t_v2d_d){-diff.y, diff.x};
		apply_rotation(camera, -PI_2);
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.y -= 0.999999999;
			else
				camera->pos.y += 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.x += 0.999999999;
			else
				camera->pos.x -= 0.999999999;
		}
	}
	else if (relative_position == 2)	// opposite face
	{
		// rotate vector (diff) 0 degrees relative to the portal
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff.x = -diff.x;
		diff.y = -diff.y;
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.x += 0.999999999;
			else
				camera->pos.x -= 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.y += 0.999999999;
			else
				camera->pos.y -= 0.999999999;
		}
	}
	else if (relative_position == 3)	// right face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff = (t_v2d_d){diff.y, -diff.x};
		apply_rotation(camera, PI_2);
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.y += 0.999999999;
			else
				camera->pos.y -= 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.x -= 0.999999999;
			else
				camera->pos.x += 0.999999999;
		}
	}
}

void	draw_view_cone(t_c3_env *env)
{
	(void)env;
	t_ray	ray;
	t_v2d_d	ray_hit;
	int		x;
	int		hit_count;
	t_v2d_i tmp;
	t_camera	camera;

	g_debug = 4;
	x = 0;
	while (x < WIDTH)
	{
		camera.pos = env->player.camera.pos;
		camera.dir = env->player.camera.dir;
		camera.plane = env->player.camera.plane;
		hit_count = 0;
		ray = (t_ray){0};
		while ((NOT_WALL(ray.hit_type) && !(IS_PORTAL(ray.hit_type) && -1 == env->scene.portals.tab[GET_PORTAL(ray.hit_type)].linked_portal)) && hit_count < MAX_LAYERS)
		{
			if (IS_PORTAL(ray.hit_type))
				fake_portal_hit(&env->scene, &ray, &camera);
			screen_ray_calculation(&camera, &ray, x);
			ft_dda(&env->scene, &ray);
			ray_hit.x = camera.pos.x + ray.ray_dir.x * (ray.perp_wall_dist);
			ray_hit.y = camera.pos.y + ray.ray_dir.y * (ray.perp_wall_dist);
			draw_line(&env->img,
				(int)(camera.pos.x * MINIMAP_SCALE),
				(int)(camera.pos.y * MINIMAP_SCALE),
				(int)(ray_hit.x * MINIMAP_SCALE),
				(int)(ray_hit.y * MINIMAP_SCALE),
				0x007F00);
			tmp = (t_v2d_i){(int)(camera.pos.x * MINIMAP_SCALE), (int)(camera.pos.y * MINIMAP_SCALE)};
			draw_rectangle(&env->img, tmp, (t_v2d_i){2, 2}, 0xff7eeb);
			tmp = (t_v2d_i){(int)(ray_hit.x * MINIMAP_SCALE), (int)(ray_hit.y * MINIMAP_SCALE)};
			draw_rectangle(&env->img, tmp, (t_v2d_i){2, 2}, 0x11d280);
			camera.pos = ray_hit;
			hit_count++;
		}
		x++;
	}
	g_debug = 0;
}
