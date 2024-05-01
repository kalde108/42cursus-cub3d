/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:49:50 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:09:27 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"

int	ft_vector_alloc(t_vector **ptr, t_vinfos infos, size_t n)
{
	t_vector	*new;
	size_t		i;

	if (!n)
		return (FAILURE);
	new = malloc(sizeof(t_vector) * n);
	if (!new)
		return (FAILURE);
	i = 0;
	while (i < n)
	{
		if (ft_vector_init(new + i, infos))
		{
			while (i--)
				ft_vector_free(new + i);
			free(new);
			return (FAILURE);
		}
		i++;
	}
	*ptr = new;
	return (SUCCESS);
}
