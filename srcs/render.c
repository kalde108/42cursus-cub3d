#include "mlx.h"
#include "cub3d.h"
#include "draw.h"
#include "key_index.h"
#include <math.h>

# include <stdio.h>

char	worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	simple_raycasting(t_c3_env *env)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		double	cameraX;
		double	rayDirX;
		double	rayDirY;

		cameraX = 2 * x / (double)WIDTH - 1;
		rayDirX = env->dirX + env->planeX * cameraX;
		rayDirY = env->dirY + env->planeY * cameraX;

		int mapX;
		int mapY;

		mapX = (int)env->posX;
		mapY = (int)env->posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX;
		double deltaDistY;

		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		
		double perpWallDist;

		int stepX;
		int stepY;

		int hit;
		int side;

		hit = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (env->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - env->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (env->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - env->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - env->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - env->posY + (1 - stepY) / 2) / rayDirY;
		
		int lineHeight;

		lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart;
		int drawEnd;

		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		
		int color;

		if (worldMap[mapX][mapY] == 1)
			color = 0x00FF0000;
		else if (worldMap[mapX][mapY] == 2)
			color = 0x0000FF00;
		else if (worldMap[mapX][mapY] == 3)
			color = 0x000000FF;
		else if (worldMap[mapX][mapY] == 4)
			color = 0x00FFFF00;
		else
			color = 0x00FFFFFF;
		
		if (side == 1)
			color = color / 2;
		
		draw_v_line(env, x, drawStart, drawEnd, color);
		x++;
	}
}

int	render(t_c3_env *env)
{
	// printf("render\n");
	clean_screen(env);

	simple_raycasting(env);

	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
