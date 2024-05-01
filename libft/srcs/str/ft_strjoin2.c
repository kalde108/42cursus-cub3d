/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:10:22 by ibertran          #+#    #+#             */
/*   Updated: 2024/03/08 18:15:49 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

#include "ft_string.h"
#include "ft_mem.h"

char	*ft_strjoin2(char const *s1, char const *s2, char const *s3)
{
	const size_t	len1 = ft_strlen(s1);
	const size_t	len2 = ft_strlen(s2);
	const size_t	len3 = ft_strlen(s3);
	char			*ptr;

	ptr = malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len1 + len2 + len3] = '\0';
	ft_memcpy(ptr, s1, len1);
	ft_memcpy(ptr + len1, s2, len2);
	ft_memcpy(ptr + len1 + len2, s3, len3);
	return (ptr);
}
