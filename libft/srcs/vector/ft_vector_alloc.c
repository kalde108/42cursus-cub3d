/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:49:50 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 13:58:00 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"

int	ft_vector_alloc(t_vector **ptr,
				size_t data_size,
				size_t capacity,
				void (*del)(void *))
{
	t_vector	*new;

	new = malloc(sizeof(t_vector));
	if (!new)
		return (FAILURE);
	if (ft_vector_init(new, data_size, capacity, del))
	{
		ft_vector_free(new);
		free(new);
		return (FAILURE);
	}
	*ptr = new;
	return (SUCCESS);
}
