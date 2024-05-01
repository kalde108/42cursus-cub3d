/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprint_vchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:26:12 by ibertran          #+#    #+#             */
/*   Updated: 2024/03/13 06:26:26 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	ft_vprint_vchar(void *ptr, size_t index)
{
	(void)index;
	ft_vector_print((t_vector *)ptr, ft_vprint_char, NULL);
}
