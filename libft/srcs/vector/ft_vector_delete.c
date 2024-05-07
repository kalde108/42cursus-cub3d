/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:09:31 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 14:02:50 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_delete(t_vector *v, size_t index)
{
	if (!v || index >= v->total)
		return (FAILURE);
	if (v->infos.del)
		v->infos.del((void **)ft_vector_get(v, index));
	ft_memcpy(v->ptr + index * v->infos.data_size,
		v->ptr + (index + 1) * v->infos.data_size,
		(v->total - 1 - index) * v->infos.data_size);
	v->total--;
	return (SUCCESS);
}
