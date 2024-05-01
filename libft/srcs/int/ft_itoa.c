/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:38:56 by ibertran          #+#    #+#             */
/*   Updated: 2023/12/01 16:31:44 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	char	*ptr;
	long	lnbr;
	size_t	len;

	len = ft_itoalen(nbr);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	lnbr = (long)nbr;
	if (nbr < 0)
		lnbr *= -1;
	while (len--)
	{
		ptr[len] = lnbr % 10 + '0';
		lnbr /= 10;
	}
	if (nbr < 0)
		ptr[0] = '-';
	return (ptr);
}

char	*ft_itoa_base(int nbr, char *base)
{
	char	*ptr;
	long	lnbr;
	int		len;
	int		base_len;

	base_len = ft_strlen(base);
	len = ft_itoalen_base(nbr, base);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	lnbr = (long)nbr;
	if (nbr < 0)
		lnbr *= -1;
	while (len--)
	{
		ptr[len] = base[lnbr % base_len];
		lnbr /= base_len;
	}
	if (nbr < 0)
		ptr[0] = '-';
	return (ptr);
}

char	*ft_uitoa_base(unsigned int nbr, char *base)
{
	char			*ptr;
	unsigned long	lnbr;
	int				len;
	int				base_len;

	base_len = ft_strlen(base);
	len = ft_uitoalen_base(nbr, base);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	lnbr = (long)nbr;
	while (len--)
	{
		ptr[len] = base[lnbr % base_len];
		lnbr /= base_len;
	}
	return (ptr);
}

char	*ft_ulltoa_base(unsigned long long nbr, char *base)
{
	char	*ptr;
	int		len;
	int		base_len;

	base_len = ft_strlen(base);
	len = ft_ulltoalen_base(nbr, base);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (len--)
	{
		ptr[len] = base[nbr % base_len];
		nbr /= base_len;
	}
	return (ptr);
}
