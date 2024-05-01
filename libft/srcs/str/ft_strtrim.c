/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:50:15 by ibertran          #+#    #+#             */
/*   Updated: 2023/11/20 10:37:54 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	start = 0;
	while (ft_ischarset(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_ischarset(s1[end], set))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
