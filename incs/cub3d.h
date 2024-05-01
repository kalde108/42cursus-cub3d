#ifndef CUB3D_H
# define CUB3D_H

# include <cubscene.h>

int		check_scene_format(char *path);
int		get_cubscene(char *path, t_cubscene *ptr);

int		init_scene(t_cubscene *ptr);
void	destroy_scene(t_cubscene *ptr);

#endif //CUB3D_H