/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoalen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 02:05:54 by ibertran          #+#    #+#             */
/*   Updated: 2023/12/01 16:33:20 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoalen(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_itoalen_base(int n, char *base)
{
	int	i;
	int	base_len;

	base_len = ft_strlen(base);
	i = 1;
	if (n < 0)
		i++;
	while (n / base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

int	ft_uitoalen_base(unsigned int n, char *base)
{
	int	i;
	int	base_len;

	base_len = ft_strlen(base);
	i = 1;
	while (n / base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

int	ft_ulltoalen_base(unsigned long long nbr, char *base)
{
	int	i;
	int	base_len;

	base_len = ft_strlen(base);
	i = 1;
	while (nbr / base_len)
	{
		nbr /= base_len;
		i++;
	}
	return (i);
}
