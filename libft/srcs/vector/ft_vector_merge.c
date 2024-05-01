/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:25:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:36:20 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_merge(t_vector *v1, size_t index, t_vector *v2)
{
	if (!v1 || !v2 || index > v1->total
		|| v1->infos.data_size != v2->infos.data_size)
		return (FAILURE);
	while (v1->total + v2->total > v1->infos.capacity)
	{
		if (ft_vector_resize(v1, v1->infos.capacity << 1))
			return (FAILURE);
	}
	ft_memmove(v1->ptr + v1->infos.data_size * (index + v2->total),
		v1->ptr + v1->infos.data_size * index,
		v1->infos.data_size * (v1->total - index));
	ft_memcpy(v1->ptr + v1->infos.data_size * index,
		v2->ptr,
		v2->infos.data_size * v2->total);
	v1->total += v2->total;
	free(v2->ptr);
	return (SUCCESS);
}
