#include "mlx.h"
#include "mlx_tools.h"
#include "cub3d.h"
#include <X11/Xutil.h>

# include <unistd.h>
# include <stdio.h>
# include <math.h>

char	**test_map;
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

	void DEBUG_print_vector_map(t_vector *map); //REMOVE

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
		|| get_player_spawn(test_map, &env.player))
	{
		destroy_scene(&env.scene);
		return (1);
	}
	DEBUG_print_vector_map(&env.scene.map);
	printf("\nPLAYER SPAWN(%fx,%fy)\nDIRECTION(%fx,%fy)\n\n", env.player.pos.x, env.player.pos.y, env.player.dir.x, env.player.dir.y);

	env.player.mv_speed = 0.03;
	env.player.rt_speed = 0.01;

	tmp1.x = env.player.dir.x + env.player.plane.x * -1;
	tmp1.y = env.player.dir.y + env.player.plane.y * -1;

	tmp2.x = env.player.dir.x + env.player.plane.x;
	tmp2.y = env.player.dir.y + env.player.plane.y;

	// double		magnitude1;
	// double		magnitude2;

	// magnitude1 = sqrt(pow(env.player.dir.x, 2) + pow(env.player.dir.y, 2));
	// magnitude2 = sqrt(pow(env.player.plane.x, 2) + pow(env.player.plane.y, 2));

	// // Calculate the field of view
	dot = tmp1.x * tmp2.x + tmp1.y * tmp2.y;
	dprintf(2, "dot: %f\n", dot);
	det = tmp1.x * tmp2.y - tmp1.y * tmp2.x;
	// det = 0.66;
	dprintf(2, "det: %f\n", det);
	fov = (atan2(det, dot)) * 180.0 / PI;

	// fov = acos(dot / (magnitude1 * magnitude2)) * 180.0 / PI;

	// dprintf(2, "atan2(det, dot): %f\n", atan2(det, dot));
	// dprintf(2, "(atan2(det, dot)) * 180.0: %f\n", (atan2(det, dot)) * 180.0);
	dprintf(2, "fov: %f\n", fov);



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
