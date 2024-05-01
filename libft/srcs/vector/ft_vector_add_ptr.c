/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:09:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:28:35 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

int	ft_vector_add_ptr(t_vector *v, void *item)
{
	if (!v)
		return (FAILURE);
	if (v->total == v->infos.capacity)
		if (ft_vector_resize(v, v->infos.capacity << 1))
			return (FAILURE);
	*((void **)v->ptr + v->total) = item;
	v->total++;
	return (SUCCESS);
}
