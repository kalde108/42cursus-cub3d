/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsort_str_ascending.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:05:30 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/29 17:05:58 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"
#include "ft_vector.h"

int	vsort_str_ascending(void *ptr1, void*ptr2)
{
	const char	*str1 = ((t_vector *)ptr1)->ptr;
	const char	*str2 = ((t_vector *)ptr2)->ptr;
	char		c1;
	char		c2;
	size_t		i;

	i = 0;
	c1 = ft_tolower(str1[i]);
	c2 = ft_tolower(str2[i]);
	while (c1 && c2 && c1 == c2)
	{
		i++;
		c1 = ft_tolower(str1[i]);
		c2 = ft_tolower(str2[i]);
	}
	return ((c1 - c2) > 0);
}
