/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:13:03 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/14 05:25:18 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_countwords(const char *str, const char *sep)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_ischarset(str[i], sep)
			&& (ft_ischarset(str[i + 1], sep) || !str[i + 1]))
			count++;
		i++;
	}
	return (count);
}
