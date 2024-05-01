/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:16:28 by ibertran          #+#    #+#             */
/*   Updated: 2023/11/14 16:13:21 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (n == 0)
		return (NULL);
	i = 0;
	while (i < n - 1 && ((unsigned char *)s)[i] != (unsigned char)c)
		i++;
	if (((unsigned char *)s)[i] == (unsigned char)c)
		return ((unsigned char *)s + i);
	else
		return (NULL);
}
