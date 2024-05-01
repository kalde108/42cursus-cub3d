/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_trim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 04:01:20 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:29:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_trim(t_vector *v)
{
	void	*new;

	if (!v)
		return (FAILURE);
	if (v->total == v->infos.capacity)
		return (SUCCESS);
	new = malloc(v->infos.data_size * v->total);
	if (!new)
		return (FAILURE);
	ft_memcpy(new, v->ptr, v->infos.data_size * v->total);
	free(v->ptr);
	v->ptr = new;
	v->infos.capacity = v->total;
	return (SUCCESS);
}
