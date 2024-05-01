/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprint_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 04:57:43 by ibertran          #+#    #+#             */
/*   Updated: 2024/03/13 05:19:32 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

#include "libft.h"

void	ft_vprint_int(void *ptr, size_t index)
{
	(void)index;
	if (!ptr)
		return ;
	printf("%d ", *(int *)ptr);
}
