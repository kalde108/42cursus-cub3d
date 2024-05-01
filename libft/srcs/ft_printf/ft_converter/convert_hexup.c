/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hexup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:07:47 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:07:49 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_integer.h"
#include "ft_string.h"
#include <stdlib.h>

int	convert_hexup(t_vector *buffer, va_list *args)
{
	size_t	nb;
	char	*str;
	int		error;

	nb = va_arg(*args, int);
	str = ft_ulltoa_base(nb, "0123456789ABCDEF");
	if (!str)
		return (FAILURE);
	error = ft_vector_join(buffer, str, ft_strlen(str));
	free(str);
	return (error);
}
