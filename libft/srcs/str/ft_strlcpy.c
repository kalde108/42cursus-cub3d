/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:52:34 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:08:38 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (!size)
		return (src_len);
	while (*(src) && size-- > 1)
		*(dst++) = *(src++);
	*(dst) = '\0';
	return (src_len);
}
