/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:12 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 13:54:14 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_vector.h"

#include <unistd.h>
#include <stdlib.h>

int	get_fd_content(int fd, char **content)
{
	char		*line;
	t_vector	v;
	int			ret;

	if (ft_vector_init(&v, sizeof(char), 0, NULL))
		return (-1);
	line = NULL;
	ret = get_next_line(fd, &line);
	while (line)
	{
		ret = ft_vector_strncat(&v, line, ft_strlen(line));
		free(line);
		if (!ret)
			ret = get_next_line(fd, &line);
	}
	if (ret)
	{
		ft_vector_free(&v);
		return (-1);
	}
	*content = v.ptr;
	return (0);
}
