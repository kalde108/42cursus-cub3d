/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprint_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:41:32 by ibertran          #+#    #+#             */
/*   Updated: 2024/03/13 13:54:35 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_vprint_str(void *ptr, size_t index)
{
	(void)index;
	if (!ptr)
		return ;
	printf("str%3ld: %s\n", index, *(char **)ptr);
}
