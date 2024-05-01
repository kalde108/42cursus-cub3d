/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:05:17 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/15 04:42:03 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy2(void *dest, const void *src_start, void *src_end)
{
	size_t	i;

	i = 0;
	while (src_start + i <= src_end)
	{
		((char *)dest)[i] = ((char *)src_start)[i];
		i++;
	}
	return (dest);
}
