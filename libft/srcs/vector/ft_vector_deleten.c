/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_deleten.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:33:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_deleten(t_vector *v, size_t index, size_t n)
{
	size_t	i;

	if (!v || index >= v->total || index + n > v->total)
		return (FAILURE);
	if (v->infos.del)
	{
		i = index;
		while (i < index + n)
		{
			v->infos.del((void **)ft_vector_get(v, i));
			i++;
		}
	}
	ft_memcpy(v->ptr + index * v->infos.data_size,
		v->ptr + (index + n) * v->infos.data_size,
		(v->total - n - index) * v->infos.data_size);
	v->total -= n;
	while (v->infos.capacity > 1 && v->total <= (v->infos.capacity >> 2))
		if (ft_vector_resize(v, v->infos.capacity >> 1))
			return (FAILURE);
	return (SUCCESS);
}
