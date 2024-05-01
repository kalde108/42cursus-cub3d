/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:10:14 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:30:12 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_free(t_vector *v)
{
	size_t	i;

	if (!v)
		return (FAILURE);
	if (v->infos.del)
	{
		i = 0;
		while (i < v->total)
			v->infos.del((void **)ft_vector_get(v, i++));
	}
	free(v->ptr);
	ft_memset(v, '\0', sizeof(t_vector));
	return (SUCCESS);
}
