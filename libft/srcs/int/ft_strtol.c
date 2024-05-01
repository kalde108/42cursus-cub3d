/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:38:05 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/16 02:28:50 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include "libft.h"

static int	strtol_init(const char *s, const char **endptr, int *base);
static long	strtol_accretion(const char *s, const char **endptr, int base, \
																	int sign);
static int	strtol_value(char *value, int base);

long	ft_strtol(const char *ptr, char **endptr)
{
	unsigned long	acc;
	int				base;
	int				sign;
	const char		*s;

	s = ptr;
	base = 10;
	sign = strtol_init(s, &s, &base);
	acc = strtol_accretion(s, &s, base, sign);
	if (endptr)
		*endptr = (char *)s;
	if (errno == ERANGE)
	{
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	return (acc * sign);
}

static int	strtol_init(const char *s, const char **endptr, int *base)
{
	int			sign;
	char		c;

	c = *s++;
	while (ft_isspace(c))
		c = *s++;
	if (c == '-')
	{
		sign = -1;
		c = *s++;
	}
	else
	{
		sign = 1;
		if (c == '+')
			c = *s++;
	}
	if (c == '0' && *s == 'x')
	{
		*base = 16;
		s += 2;
	}
	*endptr = s - 1;
	return (sign);
}

static long	strtol_accretion(const char *s, const char **endptr, int base, \
																	int sign)
{
	long	acc;
	char	c;

	acc = 0;
	c = *s++;
	while (c)
	{
		if (strtol_value(&c, base) == -1)
			break ;
		if (sign == 1 && (LONG_MAX / base < acc || base * acc > LONG_MAX - c))
			errno = ERANGE;
		if (sign == -1 && (LONG_MIN / base > acc || base * -acc < LONG_MIN + c))
			errno = ERANGE;
		acc = acc * base + c;
		c = *s++;
	}
	*endptr = s - 1;
	return (acc);
}

static int	strtol_value(char *value, int base)
{
	const char	c = *value;

	if (c >= '0' && c <= '9')
		*value -= '0';
	else if (c >= 'A' && c <= 'Z')
		*value -= 'A' - 10;
	else if (c >= 'a' && c <= 'z')
		*value -= 'a' - 10;
	else
		return (-1);
	if (*value >= base)
	{
		errno = EINVAL;
		return (-1);
	}
	return (0);
}
