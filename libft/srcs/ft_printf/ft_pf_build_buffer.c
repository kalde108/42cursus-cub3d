/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_build_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:07:32 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:07:34 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_printf.h"

int	pf_build_buffer(const char *str, t_vector *buffer, va_list *args)
{
	int		status;
	char	c;

	status = SUCCESS;
	c = *str++;
	while (c && !status)
	{
		if (c != '%')
			status = ft_vector_add(buffer, &c);
		else
		{
			status = add_conversion(*str, buffer, args);
			str++;
		}
		c = *str++;
	}
	if (!status)
		status = ft_vector_add(buffer, "\0");
	return (status);
}
