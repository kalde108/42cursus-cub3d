/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_print_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:07:38 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:07:39 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>

#include "ft_vector.h"

int	print_buffer(int fd, t_vector *buffer)
{
	ssize_t	status;

	status = write(fd, buffer->ptr, buffer->total - 1);
	ft_vector_free(buffer);
	return (status);
}
