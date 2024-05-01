/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:19 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 17:38:43 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_init(t_vector *v, t_vinfos infos)
{
	if (!v || infos.data_size < 1)
		return (FAILURE);
	v->infos = infos;
	if (infos.capacity < 1)
		v->infos.capacity = VECTOR_INIT_CAPACITY;
	else
		v->infos.capacity = infos.capacity;
	v->total = 0;
	v->ptr = malloc(v->infos.data_size * v->infos.capacity);
	if (!v->ptr)
	{
		ft_memset(v, '\0', sizeof(t_vector));
		return (FAILURE);
	}
	ft_memset(v->ptr, 0, v->infos.data_size);
	return (SUCCESS);
}

