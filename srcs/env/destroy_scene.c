#include <stdlib.h>

#include "cubscene.h"
#include "libft.h"

static void	destroy_scene_textures(t_cubscene *scene);

void	destroy_scene(t_cubscene *scene)
{
	destroy_scene_textures(scene);
	free(scene->map);
}

static void	destroy_scene_textures(t_cubscene *scene)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		free(scene->texture[i].filepath);
		free(scene->texture[i].ptr);
		i++;
	}
}
