/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 03:38:44 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/05 18:13:29 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_sprintf(const char *str, ...)
{
	va_list		args;
	t_vector	buffer;

	if (!str || ft_vector_init(&buffer, (t_vinfos){sizeof(char), 0, NULL}))
		return (NULL);
	va_start(args, str);
	if (pf_build_buffer(str, &buffer, &args))
	{
		va_end(args);
		ft_vector_free(&buffer);
		return (NULL);
	}
	va_end(args);
	if (ft_vector_trim(&buffer))
	{
		ft_vector_free(&buffer);
		return (NULL);
	}
	return (buffer.ptr);
}
