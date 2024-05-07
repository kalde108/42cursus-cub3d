/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 03:38:44 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 13:53:58 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_printf.h"

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list		args;
	t_vector	buffer;

	if (!str || ft_vector_init(&buffer, sizeof(char), 0, NULL))
		return (FAILURE);
	va_start(args, str);
	if (pf_build_buffer(str, &buffer, &args))
	{
		va_end(args);
		ft_vector_free(&buffer);
		return (FAILURE);
	}
	va_end(args);
	return (print_buffer(fd, &buffer));
}
