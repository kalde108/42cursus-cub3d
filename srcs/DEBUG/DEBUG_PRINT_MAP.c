#include <stdio.h>
#include "libft.h"

#include "cubscene.h"

void	DEBUG_PRINT_MAP(t_cubscene scene)
{
	int i;

	i = 0;
	while (i < scene.width * scene.height)
	{
		char c = scene.map[i];
		if ( c == '1')
			printf("%s  %s", "\e[41m", "\e[0m");
		else if (c == '0')
			printf("%s  %s", "\e[40m", "\e[0m");
		else if (c == ' ')
			printf("..");
		else
			printf("%c ", c);
		i++;
		if (i % scene.width == 0)
			printf("\n");
	}
}
