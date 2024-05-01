/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:11:00 by ibertran          #+#    #+#             */
/*   Updated: 2023/11/23 13:54:01 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!dst && !size)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (len > size)
		len = size;
	if (len < size)
	{
		i = 0;
		while (src[i] && len + i < size - 1)
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = '\0';
	}
	return (len + ft_strlen(src));
}
