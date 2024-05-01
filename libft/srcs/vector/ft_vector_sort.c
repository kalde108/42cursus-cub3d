/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:58:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:29:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

static void	swap_elements(t_vector *v, size_t index, void *tmp);

int	ft_vector_sort(t_vector *v, int (*cmp)(void *, void *))
{
	size_t	index;
	void	*tmp;

	if (!v || !cmp)
		return (FAILURE);
	if (!v->total)
		return (SUCCESS);
	tmp = malloc(v->infos.data_size);
	if (!tmp)
		return (FAILURE);
	index = 0;
	while (index < v->total - 1)
	{
		if (cmp(ft_vector_get(v, index), ft_vector_get(v, index + 1)))
		{
			swap_elements(v, index, tmp);
			index = 0;
		}
		else
			index++;
	}
	free(tmp);
	return (SUCCESS);
}

static void	swap_elements(t_vector *v, size_t index, void *tmp)
{
	ft_memcpy(tmp,
		v->ptr + index * v->infos.data_size,
		v->infos.data_size);
	ft_memcpy(v->ptr + index * v->infos.data_size,
		v->ptr + (index + 1) * v->infos.data_size,
		v->infos.data_size);
	ft_memcpy(v->ptr + (index + 1) * v->infos.data_size,
		tmp,
		v->infos.data_size);
}
