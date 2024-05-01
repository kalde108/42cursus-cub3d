/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:41 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:29:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"
#include <stdlib.h>

int	ft_vector_resize(t_vector *v, size_t capacity)
{
	void	*new;

	if (!v || capacity < v->total || !capacity)
		return (FAILURE);
	new = malloc(v->infos.data_size * capacity);
	if (!new)
		return (FAILURE);
	ft_memcpy(new, v->ptr, v->infos.data_size * v->total);
	free(v->ptr);
	v->ptr = new;
	v->infos.capacity = capacity;
	return (SUCCESS);
}
