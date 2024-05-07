#include "player.h"
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

static void	step_init(t_player *player, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map_pos.x) \
							* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - player->pos.x) \
							* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map_pos.y) \
							* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - player->pos.y) \
							* ray->delta_dist.y;
	}
}

void	ray_calculation(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = (2 * x / (double)WIDTH - 1);
	ray->ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray->ray_dir.y = player->dir.y + player->plane.y * camera_x;
	delta_dist_init(ray);
	ray->map_pos.x = (int)player->pos.x;
	ray->map_pos.y = (int)player->pos.y;
	step_init(player, ray);
}
