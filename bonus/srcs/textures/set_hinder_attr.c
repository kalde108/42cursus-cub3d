#include <errno.h>
#include <unistd.h>

#include "textures.h"
#include "libft.h"
#include "cubdef.h"

int set_hinder_attr(char *identifier, char *str,  t_elem *elem)
{
	long value;
	char *end_ptr;

	errno = 0;
	value = ft_strtol(str, &end_ptr);
	if (errno == ERANGE || value < 0 || value > 100 || '\0' != *end_ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_HINDER);
		return (1);
	}
	elem->attr.hinder = value  * 0.01;
	return (0);
}
