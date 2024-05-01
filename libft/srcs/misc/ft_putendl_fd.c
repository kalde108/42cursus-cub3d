/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:50 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:08:52 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

long	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	if (write(fd, s, len) == -1)
		return (-1);
	return (write(fd, "\n", 1));
}
