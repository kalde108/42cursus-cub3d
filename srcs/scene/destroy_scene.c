#include <stdlib.h>

#include "cubscene.h"
#include "libft.h"

void	destroy_scene(t_cubscene *ptr)
{
	free(ptr->texture.no.filepath);
	free(ptr->texture.so.filepath);
	free(ptr->texture.ea.filepath);
	free(ptr->texture.we.filepath);
	free(ptr->map);
}

void	destroy_texture(t_img *img)
{
	free(img->filepath);
	free(img->ptr); //
}