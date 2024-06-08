#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

#include <math.h>

# include "libft.h"
# include <stdio.h>

void	draw_view_cone(t_c3_env *env, double angle)
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

			hit_buf->camera.pos.x = ((hit_buf->camera.pos.x - env->player.camera.pos.x) * env->options.minimap.zoom + env->options.minimap.pos.x);
			hit_buf->camera.pos.y = ((hit_buf->camera.pos.y - env->player.camera.pos.y) * env->options.minimap.zoom + env->options.minimap.pos.y);
			line_start.x = ((line_start.x - env->player.camera.pos.x) * env->options.minimap.zoom + env->options.minimap.pos.x);
			line_start.y = ((line_start.y - env->player.camera.pos.y) * env->options.minimap.zoom + env->options.minimap.pos.y);
			ray_hit.x = ((ray_hit.x - env->player.camera.pos.x) * env->options.minimap.zoom + env->options.minimap.pos.x);
			ray_hit.y = ((ray_hit.y - env->player.camera.pos.y) * env->options.minimap.zoom + env->options.minimap.pos.y);
			if (!env->options.minimap.lock)
			{
				ft_rotate_v2_around(&hit_buf->camera.pos, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
				ft_rotate_v2_around(&line_start, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
				ft_rotate_v2_around(&ray_hit, angle, (t_v2d_d){env->options.minimap.pos.x, env->options.minimap.pos.y});
			}

			draw_line_minimap(&env->img, (int)(line_start.x), (int)(line_start.y), (int)(ray_hit.x), (int)(ray_hit.y), (t_color){0x007F00}, env);

			int	dot_size;
			dot_size = 0.1 * env->options.minimap.zoom + 1.0;
			// dprintf(2, "dot_size: %d\n", dot_size);
			if (is_on_minimap(&env->options.minimap, (int)(hit_buf->camera.pos.x), (int)(hit_buf->camera.pos.y)))
				draw_rectangle(&env->img, (t_v2d_i){(int)(hit_buf->camera.pos.x), (int)(hit_buf->camera.pos.y)}, (t_v2d_i){dot_size, dot_size}, (t_color){0xffffff});
			if (is_on_minimap(&env->options.minimap, (int)(line_start.x), (int)(line_start.y)))
				draw_rectangle(&env->img, (t_v2d_i){(int)(line_start.x), (int)(line_start.y)}, (t_v2d_i){dot_size, dot_size}, (t_color){0xff7eeb});
			if (is_on_minimap(&env->options.minimap, (int)(ray_hit.x), (int)(ray_hit.y)))
				draw_rectangle(&env->img, (t_v2d_i){(int)(ray_hit.x), (int)(ray_hit.y)}, (t_v2d_i){dot_size, dot_size}, (t_color){0x11d280});

			prev_z = hit_buf->z;
			i++;
		}
		x++;
	}
}
