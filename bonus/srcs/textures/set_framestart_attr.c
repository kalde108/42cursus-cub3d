#include <stdlib.h>
#include <unistd.h>

#include "textures.h"
#include "libft.h"
#include "cubdef.h"

# include <stdio.h>

int set_framestart_attr(char *identifier, char *str,  t_elem *elem)
{
	long value;
	char *end_ptr;

	value = ft_strtol(str, &end_ptr);
	if (0 > value || elem->n < value || '\0' != *end_ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_FRAMESTART);
		return (1);
	}
	if (0 == value)
		elem->current_frame = rand() % elem->n;
	else
		elem->current_frame = value - 1;
	elem->current = elem->frames + elem->current_frame;
	return (0);
}
