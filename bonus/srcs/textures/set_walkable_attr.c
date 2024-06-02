#include <unistd.h>
#include <errno.h>

#include "cubdef.h"
#include "textures.h"
#include "libft.h"

int set_walkable_attr(char *identifier, char *str,  t_elem *elem)
{
	const char	*value[] = {YES, NO, NULL};
	t_anim		i;

	i = 0;
	while (NULL != value[i])
	{
		if (0 == ft_strcmp(value[i], str))
		{
			elem->attr.walkable = (0 == i);
			return (0);
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_WALKABLE);
	return (1);
}
