/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:46:20 by ibertran          #+#    #+#             */
/*   Updated: 2023/11/23 15:32:38 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	if (!big && !len)
		return (NULL);
	if (!big[i] && !little[i])
		return (((char *)big));
	little_len = ft_strlen(little);
	if (little_len > len)
		return (NULL);
	while (big && big[i] && i <= len - little_len)
	{
		if (!ft_strncmp(big + i, little, little_len))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
