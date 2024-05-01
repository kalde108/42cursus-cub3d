/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_iteri.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:00:04 by ibertran          #+#    #+#             */
/*   Updated: 2024/03/15 18:12:52 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

int	ft_vector_iteri(t_vector *v, t_vfunc function)
{
	size_t	i;

	if (!v || !function)
		return (FAILURE);
	i = 0;
	while (i < v->total)
	{
		if (function(ft_vector_get(v, i)))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
