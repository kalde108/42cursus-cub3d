/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_set_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:10:47 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_set_ptr(t_vector *v, size_t index, void *item)
{
	if (!v || index >= v->total)
		return (FAILURE);
	*((void **)v->ptr + index) = item;
	return (SUCCESS);
}
