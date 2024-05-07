/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_deleten.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 14:02:56 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_deleten(t_vector *v, size_t index, size_t n)
{
	size_t	i;

	if (!v || index >= v->total || index + n > v->total)
		return (FAILURE);
	if (v->infos.del)
	{
		i = index;
		while (i < index + n)
		{
			v->infos.del((void **)ft_vector_get(v, i));
			i++;
		}
	}
	ft_memcpy(v->ptr + index * v->infos.data_size,
		v->ptr + (index + n) * v->infos.data_size,
		(v->total - n - index) * v->infos.data_size);
	v->total -= n;
	return (SUCCESS);
}
