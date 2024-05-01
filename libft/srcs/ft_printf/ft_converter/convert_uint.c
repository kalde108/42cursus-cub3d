/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:08 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:08:10 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_integer.h"
#include "ft_string.h"
#include <stdlib.h>

int	convert_uint(t_vector *buffer, va_list *args)
{
	unsigned int	nb;
	char			*str;
	int				error;

	nb = va_arg(*args, int);
	str = ft_uitoa_base(nb, "0123456789");
	if (!str)
		return (FAILURE);
	error = ft_vector_join(buffer, str, ft_strlen(str));
	free(str);
	return (error);
}
