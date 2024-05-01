/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_in_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:08:42 by ibertran          #+#    #+#             */
/*   Updated: 2024/04/19 22:08:45 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_str_in_array(const char *str, const char **array)
{
	int	i;

	if (!str || !array)
		return (-1);
	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(str, array[i]))
			return (i);
		i++;
	}
	return (-1);
}
