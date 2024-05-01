/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprint_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 04:52:29 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/05 18:13:38 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_char.h"

void	ft_vprint_char(void *ptr, size_t index)
{
	const char	cmp[] = {'\0', '\n', '\t', ' '};
	const char	*res[] = {"\\0", "\\n", "\\t", " ", NULL};
	size_t		i;

	(void)index;
	if (!ptr)
		return ;
	i = 0;
	while (res[i])
	{
		if (*(char *)ptr == cmp[i])
		{
			printf("%s%s%s", "\e[36;40m", (char *)res[i], "\e[0m");
			return ;
		}
		i++;
	}
	printf("%c", *(char *)ptr);
}
