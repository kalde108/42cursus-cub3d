/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map_charset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:34:34 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 19:32:42 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft.h"
#include "parsing.h"
#include "cubdef.h"

char	*get_map_charset(t_elem *textures)
{
	char	*wall_charset;
	char	*map_charset;

	wall_charset = get_layer_charset(textures);
	if (NULL == wall_charset)
		return (NULL);
	map_charset = ft_sprintf("%s%s", wall_charset, MAP_SPECIALS_CHARSET);
	free(wall_charset);
	return (map_charset);
}

char	*get_layer_charset(t_elem *textures)
{
	char	*charset;
	int		i;
	int		j;

	charset = malloc((MAX_TEXTURE + 2) * sizeof(char));
	if (NULL == charset)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (NULL);
	}
	i = 0;
	j = 0;
	charset[j++] = ' ';
	while (i < MAX_TEXTURE)
	{
		if (NULL != textures[i].frames)
		{
			charset[j] = 'a' + i;
			j++;
		}
		i++;
	}
	charset[j] = '\0';
	return (charset);
}

