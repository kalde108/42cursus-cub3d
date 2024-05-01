/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:07:27 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:07:29 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_char(t_vector *buffer, va_list *args)
{
	char	c;

	c = va_arg(*args, int);
	return (ft_vector_add(buffer, &c));
}
