/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:07:40 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/08 19:48:45 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	long	nb;

	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (ft_isdigit(nptr[i]))
	{
		if (((nb * 10 + nptr[i] - '0') / 10 != nb))
			return (((LONG_MAX * (sign > 0)) + ((LONG_MIN) * (sign < 0))));
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}
