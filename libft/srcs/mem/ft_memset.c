/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:14:29 by ibertran          #+#    #+#             */
/*   Updated: 2023/11/13 09:42:45 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*ret;
	size_t	i;

	ret = s;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = (char)c;
		i++;
	}
	return (ret);
}
