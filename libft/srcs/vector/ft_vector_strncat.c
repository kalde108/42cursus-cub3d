/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_strncat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:36:51 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_strncat(t_vector *v, char *str, size_t len)
{
	if (!v)
		return (FAILURE);
	if (!len)
		return (SUCCESS);
	if (v->total > 0 && *(char *)ft_vector_get(v, v->total - 1) == '\0')
		v->total--;
	while (v->total + len + 1 > v->infos.capacity)
	{
		if (ft_vector_resize(v, v->infos.capacity << 1))
			return (FAILURE);
	}
	ft_memcpy(v->ptr + v->infos.data_size * v->total,
		str,
		v->infos.data_size * len);
	*((char *)v->ptr + v->infos.data_size * (v->total + len)) = '\0';
	v->total += len + 1;
	return (SUCCESS);
}
