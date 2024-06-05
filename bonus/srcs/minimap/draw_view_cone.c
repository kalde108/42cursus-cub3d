#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

#include <math.h>

# include "libft.h"
# include <stdio.h>

void	draw_view_cone(t_c3_env *env)
{
	int				x;
	t_hit_buffer	*hit_buf;
	t_ray			ray;
	t_v2d_d			ray_hit;
	t_v2d_d			line_start;
	double			prev_z;
	int				hit_count;
	int				i;

	x = 0;
	while (x < WIDTH)
	{
		ray = (t_ray){0};
		prev_z = 0;
		i = 0;
		hit_count = env->buffer[x]->count;
		while (i < hit_count)
		{
			hit_buf = env->buffer[x] + i;

			screen_ray_calculation(&hit_buf->camera, &ray, x);

			line_start = (t_v2d_d){hit_buf->camera.pos.x + ray.ray_dir.x * prev_z, hit_buf->camera.pos.y + ray.ray_dir.y * prev_z};

			ray_hit = (t_v2d_d){hit_buf->camera.pos.x + ray.ray_dir.x * hit_buf->z, hit_buf->camera.pos.y + ray.ray_dir.y * hit_buf->z};

			draw_line(&env->img, (int)(line_start.x * MINIMAP_SCALE), (int)(line_start.y * MINIMAP_SCALE), (int)(ray_hit.x * MINIMAP_SCALE), (int)(ray_hit.y * MINIMAP_SCALE), (t_color){0x007F00});

			draw_rectangle(&env->img, (t_v2d_i){(int)(hit_buf->camera.pos.x * MINIMAP_SCALE), (int)(hit_buf->camera.pos.y * MINIMAP_SCALE)}, (t_v2d_i){2, 2}, (t_color){0xff7eeb});
			draw_rectangle(&env->img, (t_v2d_i){(int)(ray_hit.x * (double)MINIMAP_SCALE), (int)(ray_hit.y * (double)MINIMAP_SCALE)}, (t_v2d_i){2, 2}, (t_color){0x11d280});

			prev_z = hit_buf->z;
			i++;
		}
		x++;
	}
}
