/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:33 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:30:12 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_replace(t_vector *v, size_t index, void *new)
{
	if (!v || index >= v->total)
		return (FAILURE);
	if (v->infos.del)
		v->infos.del((void **)ft_vector_get(v, index));
	ft_memcpy(v->ptr + index * v->infos.data_size, new, v->infos.data_size);
	return (SUCCESS);
}
