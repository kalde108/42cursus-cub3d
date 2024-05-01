/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:26:30 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:33:32 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_insert(t_vector *v, size_t index, void *item)
{
	if (!v || index > v->total)
		return (FAILURE);
	if (v->total == v->infos.capacity)
		if (ft_vector_resize(v, v->infos.capacity << 1))
			return (FAILURE);
	ft_memmove(v->ptr + v->infos.data_size * (index + 1),
		v->ptr + v->infos.data_size * index,
		v->infos.data_size * (v->total - index));
	ft_memcpy(v->ptr + v->infos.data_size * index, item, v->infos.data_size);
	v->total++;
	return (SUCCESS);
}
