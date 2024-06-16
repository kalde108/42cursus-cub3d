/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hit_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:46:56 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/16 16:46:56 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cub3d.h"
#include "libft.h"

static int	allocate_hit_buffer(t_hit_buffer **buffer)
{
	*buffer = ft_calloc(MAX_LAYERS, sizeof(t_hit_buffer));
	if (NULL == *buffer)
	{
		ft_dprintf(STDERR_FILENO, HITBUF_ERR, FATAL, strerror(errno));
		return (1);
	}
	return (0);
}

int	init_hit_buffer(t_c3_env *env)
{
	size_t	i;

	env->buffer = ft_calloc(WIDTH, sizeof(t_hit_buffer *));
	if (NULL == env->buffer)
	{
		ft_dprintf(STDERR_FILENO, HITBUF_ERR, FATAL, strerror(errno));
		return (1);
	}
	i = 0;
	while (i < WIDTH)
	{
		if (0 != allocate_hit_buffer(env->buffer + i))
		{
			while (i--)
				free(env->buffer[i]);
			free(env->buffer);
			return (1);
		}
		i++;
	}
	return (0);
}
