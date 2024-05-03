#include <stdio.h>

#include "cubscene.h"

void	DEBUG_print(t_cubscene *ptr)
{
	printf("\t---------------------------------------------\n");
	printf("\t                 SCENE INFOS\n");
	printf("\t---------------------------------------------\n");
	printf("\tTEXTURE NORTH: %s\n", ptr->texture.north);
	printf("\tTEXTURE SOUTH: %s\n", ptr->texture.south);
	printf("\t TEXTURE EAST: %s\n", ptr->texture.east);
	printf("\t TEXTURE WEST: %s\n", ptr->texture.west);
	printf("\t---------------------------------------------\n");
	printf("\t        FLOOR: %d,%d,%d\n", ptr->floor.r, ptr->floor.g, ptr->floor.b);
	printf("\t     CEILLING: %d,%d,%d\n", ptr->ceilling.r, ptr->ceilling.g, ptr->ceilling.b);
	printf("\t---------------------------------------------\n");

}
