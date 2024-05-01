/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:17 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:08:19 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "get_next_line.h"
#include "ft_string.h"
#include <unistd.h>

static int	get_from_buffer(char *buffer, t_vector *v)
{
	size_t	len;
	char	*tmp;

	tmp = ft_strchr(buffer, '\n');
	if (tmp)
	{
		tmp = tmp + 1;
		len = ft_strlcpy(buffer, tmp, BUFFER_SIZE);
		buffer[len] = '\0';
		tmp = ft_strchr(buffer, '\n');
		if (tmp)
			len = tmp - buffer + 1;
		if (ft_vector_strncat(v, buffer, len))
			return (-1);
	}
	return (tmp != NULL);
}

static int	gnl_read_line(char *buffer, t_vector *v, int fd)
{
	long	read_check;
	size_t	len;
	char	*tmp;

	len = -1;
	read_check = 1;
	if (ft_strchr(v->ptr, '\n'))
		return (0);
	tmp = ft_strchr(buffer, '\n');
	while (read_check > 0 && !tmp)
	{
		read_check = read(fd, buffer, BUFFER_SIZE);
		if (read_check < 0)
			return (-1);
		if (!read_check && len == -1UL)
			return (-2);
		buffer[read_check] = '\0';
		tmp = ft_strchr(buffer, '\n');
		len = read_check * !tmp + (tmp != NULL) * (tmp - buffer + 1);
		if (read_check)
			if (ft_vector_strncat(v, buffer, len))
				return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_vector	v;
	int			error;

	if (fd < 0 || fd > GNL_OPEN_MAX || BUFFER_SIZE < 1)
		return (-1);
	if (ft_vector_init(&v, (t_vinfos){sizeof(char), GNL_VECTOR_SIZE, NULL}))
		return (-1);
	error = get_from_buffer(buffer, &v);
	if (!error)
		error = gnl_read_line(buffer, &v, fd);
	if (error < 0 && v.total == 0)
		ft_vector_free(&v);
	if (error != -1)
		*line = v.ptr;
	return (error == -1);
}
