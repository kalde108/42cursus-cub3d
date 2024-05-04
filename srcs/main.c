#include "mlx.h"
#include "mlx_tools.h"
#include "cub3d.h"
#include <X11/Xutil.h>

# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define FOV 90 // Field of view in degrees (REMOVE)

char	**test_map;

void 		DEBUG_PRINT_MAP(t_cubscene scene); //REMOVE
void		DEBUG_print(t_cubscene *ptr); //REMOVE

int main(int ac, char **av)
{
	t_c3_env	env;
	t_v2d_d		tmp1;
	t_v2d_d		tmp2;
	double		dot;	// Dot product of the player's direction and the camera plane
	double		det;	// Determinant of the player's direction and the camera plane
	double		fov;	// Field of view with current parameters

	env = (t_c3_env){0};
	init_scene(&env.scene);
	if (check_scene_format(av + 1)
		|| get_cubscene(av[1], &env.scene)
		|| get_player_spawn(env.scene, &env.player)
		|| !is_player_enclosed(&env.scene, &env.player))
	{
		destroy_scene(&env.scene);
		return (1);
	}
	DEBUG_print(&env.scene);
	DEBUG_PRINT_MAP(env.scene);
	printf("\nPLAYER SPAWN(%fx,%fy)\nDIRECTION(%fx,%fy)\n\n", env.player.pos.x, env.player.pos.y, env.player.dir.x, env.player.dir.y);

	env.player.mv_speed = 0.03;
	env.player.rt_speed = 0.01;


	tmp1.x = env.player.dir.x + env.player.plane.x * -1;
	tmp1.y = env.player.dir.y + env.player.plane.y * -1;

	tmp2.x = env.player.dir.x + env.player.plane.x;
	tmp2.y = env.player.dir.y + env.player.plane.y;

	// // Calculate the field of view
	dot = tmp1.x * tmp2.x + tmp1.y * tmp2.y;
	det = tmp1.x * tmp2.y - tmp1.y * tmp2.x;
	fov = (atan2(det, dot)) * 180.0 / PI;
	dprintf(2, "dot: %f\n", dot);
	dprintf(2, "det: %f\n", det);
	dprintf(2, "fov: %f\n", fov);


	// // // Calculate the perpendicular vector to player.dir
	// env.player.plane.x = -env.player.dir.y;
	// env.player.plane.y = env.player.dir.x;

	// // Normalize the perpendicular vector
	// float length = sqrt(env.player.plane.x * env.player.plane.x + env.player.plane.y * env.player.plane.y);
	// env.player.plane.x /= length;
	// env.player.plane.y /= length;

	// // Rotate the perpendicular vector by half of the FOV angle
	// float angle = FOV * 0.5 * (PI / 180.0);
	// float cosAngle = cos(angle);
	// float sinAngle = sin(angle);
	// float newX = env.player.plane.x * cosAngle - env.player.plane.y * sinAngle;
	// float newY = env.player.plane.x * sinAngle + env.player.plane.y * cosAngle;
	// env.player.plane.x = newX;
	// env.player.plane.y = newY;


	// // Calculate the perpendicular vector to player.dir
	// env.player.plane.x = -env.player.dir.y;
	// env.player.plane.y = env.player.dir.x;

	// // Normalize the perpendicular vector
	// float length = sqrt(env.player.plane.x * env.player.plane.x + env.player.plane.y * env.player.plane.y);
	// env.player.plane.x /= length;
	// env.player.plane.y /= length;

	// // Rotate the perpendicular vector by half of the FOV angle
	// float angle = FOV * 0.5 * (PI / 180.0);
	// float cosAngle = cos(angle);
	// float sinAngle = sin(angle);
	// float newX = env.player.plane.x * cosAngle - env.player.plane.y * sinAngle;
	// float newY = env.player.plane.x * sinAngle + env.player.plane.y * cosAngle;
	// env.player.plane.x = newX;
	// env.player.plane.y = newY;


	// tmp1.x = env.player.dir.x + env.player.plane.x * -1;
	// tmp1.y = env.player.dir.y + env.player.plane.y * -1;

	// tmp2.x = env.player.dir.x + env.player.plane.x;
	// tmp2.y = env.player.dir.y + env.player.plane.y;

	// // // Calculate the field of view
	// dot = tmp1.x * tmp2.x + tmp1.y * tmp2.y;
	// det = tmp1.x * tmp2.y - tmp1.y * tmp2.x;
	// fov = (atan2(det, dot)) * 180.0 / PI;
	// dprintf(2, "dot: %f\n", dot);
	// dprintf(2, "det: %f\n", det);
	// dprintf(2, "fov: %f\n", fov);




	if (ft_mlx_init(&env))
	{
		ft_mlx_free(&env);
		return (1);
	}
	mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &mlx_loop_end, env.mlx);
	mlx_hook(env.win, KeyPress, KeyPressMask, &keydown_hook, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, &keyup_hook, &env);
	mlx_loop_hook(env.mlx, &render, &env);
	mlx_loop(env.mlx);
	ft_mlx_free(&env);
	destroy_scene(&env.scene);
	return (0);
	(void)ac;
}
