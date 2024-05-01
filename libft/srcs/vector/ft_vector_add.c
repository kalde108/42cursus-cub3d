/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:07 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:29:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_add(t_vector *v, void *item)
{
	if (!v)
		return (FAILURE);
	if (v->total == v->infos.capacity)
		if (ft_vector_resize(v, v->infos.capacity << 1))
			return (FAILURE);
	ft_memcpy(v->ptr + v->total * v->infos.data_size, item, v->infos.data_size);
	v->total++;
	return (SUCCESS);
}
