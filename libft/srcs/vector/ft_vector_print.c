/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 04:49:01 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/29 16:29:17 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_vector_print(t_vector *v, void (*print)(void *, size_t), char *msg)
{
	size_t	i;

	if (!v || !print)
		return (FAILURE);
	if (msg)
		printf("%s| ", msg);
	i = 0;
	while (i < v->total)
	{
		print(ft_vector_get(v, i), i);
		i++;
	}
	printf("\n");
	return (SUCCESS);
}

int	ft_vector_printv(t_vector *v, void (*print)(void *, size_t), char *msg)
{
	size_t	i;

	if (!v || !print)
		return (FAILURE);
	if (msg)
		printf("\n%s\n", msg);
	printf("------------------------\n");
	i = 0;
	while (i < v->total)
	{
		print(ft_vector_get(v, i), i);
		i++;
	}
	printf("\n------------------------\n\n");
	return (SUCCESS);
}

int	ft_vector_printi(t_vector *v, void (*print)(void *, size_t), char *msg)
{
	size_t	i;

	if (!v || !print)
		return (FAILURE);
	if (msg)
		printf("\n%s\n", msg);
	printf("------------------------\n");
	printf(" address : %p\n", v);
	printf(" capacity: %ld/%ld\n", v->total, v->infos.capacity);
	printf(" size    : %ld\n", v->infos.data_size);
	printf("\n");
	i = 0;
	while (i < v->total)
	{
		print(ft_vector_get(v, i), i);
		i++;
	}
	printf("\n------------------------\n\n");
	return (SUCCESS);
}
