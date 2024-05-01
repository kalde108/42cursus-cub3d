/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_insertn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:26 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:34:00 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_insertn(t_vector *v, size_t index, void *item, size_t n)
{
	if (!v || index > v->total)
		return (FAILURE);
	if (!n)
		return (SUCCESS);
	while (v->total + n > v->infos.capacity)
	{
		if (ft_vector_resize(v, v->infos.capacity << 1))
			return (FAILURE);
	}
	ft_memmove(v->ptr + v->infos.data_size * (index + n),
		v->ptr + v->infos.data_size * index,
		v->infos.data_size * (v->total - index));
	ft_memcpy(v->ptr + v->infos.data_size * index,
		item, v->infos.data_size * n);
	v->total += n;
	return (SUCCESS);
}
