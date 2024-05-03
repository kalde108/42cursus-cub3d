#include "cub3d.h"
#include "raycasting.h"

#include <math.h>

static void	delta_dist_init(t_ray *ray)
{
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
}

static void	step_init(t_c3_env *env, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (env->pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - env->pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (env->pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - env->pos.y) * ray->delta_dist.y;
	}
}

void	ray_calculation(t_c3_env *env, t_ray *ray, int x)
{
	ray->ray_dir.x = env->dir.x + env->plane.x * (2 * x / (double)WIDTH - 1);
	ray->ray_dir.y = env->dir.y + env->plane.y * (2 * x / (double)WIDTH - 1);
	delta_dist_init(ray);
	ray->map_pos.x = (int)env->pos.x;
	ray->map_pos.y = (int)env->pos.y;
	step_init(env, ray);
}
