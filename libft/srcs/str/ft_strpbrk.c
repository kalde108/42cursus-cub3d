/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:06:33 by ibertran          #+#    #+#             */
/*   Updated: 2024/03/09 16:59:56 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strpbrk(const char *str1, const char *str2)
{
	const char	*ptr;
	char		c1;
	char		c2;

	c1 = *str1++;
	while (c1)
	{
		ptr = str2;
		c2 = *ptr++;
		while (c2)
		{
			if (c1 == c2)
				return ((char *)str1 - 1);
			c2 = *ptr++;
		}
		c1 = *str1++;
	}
	return (NULL);
}
