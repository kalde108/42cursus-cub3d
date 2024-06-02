#include <unistd.h>
#include <errno.h>

#include "cubdef.h"
#include "textures.h"
#include "libft.h"

int set_damage_attr(char *identifier, char *str,  t_elem *elem)
{
	long value;
	char *end_ptr;

	errno = 0;
	value = ft_strtol(str, &end_ptr);
	if (errno == ERANGE || value < 0 || '\0' != *end_ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_DAMAGE);
		return (1);
	}
	elem->attr.damage = value;
	return (0);
}
