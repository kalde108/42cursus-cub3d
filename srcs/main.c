#include "cub3d.h"

void	DEBUG_print(t_cubscene *ptr);

int	main(int ac, char **av)
{
	t_cubscene	scene;

	(void)ac;
	init_scene(&scene);
	int status = check_scene_format(av + 1) || get_cubscene(av[1], &scene);
	DEBUG_print(&scene);
	destroy_scene(&scene);
	return status; 
}
