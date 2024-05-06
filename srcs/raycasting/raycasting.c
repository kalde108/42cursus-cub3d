#include "cub3d.h"
#include "draw.h"
#include "raycasting.h"

#include <stdio.h>

int	get_tex_x(t_ray ray, double perp_wall_dist, int width, t_player player);

void	simple_raycasting(t_c3_env *env)
{
	t_ray	ray;
	int		x;
	double	perp_wall_dist;
	int		line_y[2];
	t_tex	texture;
	int		tex_x;

	// int i = 0;
	x = 0;
	while (x < WIDTH)
	{
		ray_calculation(env, &ray, x);
		ft_dda(&env->scene, &ray);
		if (ray.side == 0)
			perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
		else
			perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
		texture = get_wall_texture(ray.side, ray.ray_dir, env->scene.texture);
		tex_x = get_tex_x(ray, perp_wall_dist, texture.width, env->player);
		get_line_y(line_y, perp_wall_dist);
		// if (i++ == 2000)
		// {
		// 	printf("tex_path=%s\ntex_x=%d\ntex_width=%d\n", texture.filepath, tex_x, texture.width);
		// 	printf("color=%x\n", *(unsigned int *)texture.ptr +(tex_x * (env->img.bits_per_pixel / 8)));
		// }
		// draw_v_line(env, x, line_y[0], line_y[1], *(unsigned int *)texture.ptr + tex_x);
		x++;
	}
}
