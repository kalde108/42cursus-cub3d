#include "cub3d.h"
#include "tile_address.h"

# include "draw.h"

void	single_raycast(t_cubscene *scene, t_camera camera, t_hit_buffer hit_buf[MAX_LAYERS])
{
	t_ray			ray;
	int				hit_count;
	t_hit_buffer	*buf_ptr;

	hit_count = 0;
	ray.total_perp_wall_dist = 0;
	ray.hit_type = 0;
	while ((NOT_WALL(ray.hit_type) && !(IS_PORTAL(ray.hit_type) && -1 == scene->portals.tab[GET_PORTAL(ray.hit_type)].linked_portal)) && hit_count < MAX_LAYERS)
	{
		if (IS_PORTAL(ray.hit_type))
			portal_hit(scene, &ray, &camera);
		ray_calculation(&camera, &ray);
		ft_dda(scene, &ray);
		buf_ptr = hit_buf + hit_count;
		buf_ptr->side = ray.side;
		buf_ptr->cell = ray.hit_type;
		buf_ptr->z = ray.perp_wall_dist;
		buf_ptr->texture = get_wall_texture(scene, ray.hit_type, scene->elems);
		buf_ptr->tex_x = get_tex_x(&ray, buf_ptr->texture->width, &camera);
		get_line_y(hit_buf, ray.perp_wall_dist);
		buf_ptr->camera = camera;
		hit_count++;
	}
	hit_buf->count = hit_count;
}
