#include <stdlib.h>

#include "cubscene.h"
#include "libft.h"

void	destroy_scene(t_cubscene *ptr)
{
	free(ptr->texture.north);
	free(ptr->texture.south);
	free(ptr->texture.west);
	free(ptr->texture.east);
	free(ptr->map);
}
