/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:50 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:29:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_set(t_vector *v, size_t index, void *item)
{
	if (!v || index >= v->total)
		return (FAILURE);
	ft_memcpy(v->ptr + index * v->infos.data_size, item, v->infos.data_size);
	return (SUCCESS);
}
