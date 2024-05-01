/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:02 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:08:04 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"

int	convert_string(t_vector *buffer, va_list *args)
{
	char	*str;

	str = va_arg(*args, char *);
	if (str)
		return (ft_vector_join(buffer, str, ft_strlen(str)));
	return (ft_vector_join(buffer, "(null)", 6));
}
