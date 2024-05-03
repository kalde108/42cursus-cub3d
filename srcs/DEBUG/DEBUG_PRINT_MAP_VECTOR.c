#include <stdio.h>
#include "libft.h"

void	DEBUG_VPRINT_CUB3D(void *ptr, size_t index);

void	DEBUG_print_vector_map(t_vector *map)
{
	t_vector	*ptr;
	int			i;

	i = 0;
	ptr = ft_vector_get(map, i++);
	while (ptr)
	{
		// ft_vector_print(ptr, ft_vprint_char, NULL);
		ft_vector_print(ptr, DEBUG_VPRINT_CUB3D, NULL);
		ptr = ft_vector_get(map, i++);
	}
}

void	DEBUG_VPRINT_CUB3D(void *ptr, size_t index)
{
	char	c;

	c = *(char *)ptr;
	if (!ptr)
		return ;
	if ( c == '1')
		printf("%s %s", "\e[41m", "\e[0m");
	else if (c == '0')
		printf("%s %s", "\e[40m", "\e[0m");
	else if (c == ' ')
		printf(".");
	else
		printf("%c", *(char *)ptr);
	(void)index;
}
