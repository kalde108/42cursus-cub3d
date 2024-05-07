/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 15:39:09 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_init(t_vector *v,
				size_t data_size,
				size_t capacity,
				void (*del)(void *))
{
	v->ptr = NULL;
	v->total = 0;
	v->infos.del = del;
	if (!v || data_size < 1)
		return (FAILURE);
	v->infos.data_size = data_size;
	if (capacity < 1)
		v->infos.capacity = VECTOR_INIT_CAPACITY;
	else
		v->infos.capacity = capacity;
	v->ptr = malloc(v->infos.data_size * v->infos.capacity);
	if (!v->ptr)
		return (FAILURE);
	ft_memset(v->ptr, '\0', data_size);
	return (SUCCESS);
}
