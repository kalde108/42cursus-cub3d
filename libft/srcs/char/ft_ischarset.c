/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:37:25 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/10 16:16:40 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_ischarset(const char c, const char *set)
{
	char	*tmp;

	tmp = (char *)set;
	while (*tmp)
	{
		if (*tmp++ == c)
			return (1);
	}
	return (0);
}
