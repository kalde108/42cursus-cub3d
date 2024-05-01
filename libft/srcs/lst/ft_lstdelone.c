/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:12:59 by ibertran          #+#    #+#             */
/*   Updated: 2024/02/19 00:50:46 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "ft_lst.h"

void	ft_lstdelone(t_list *curr, void (*del)(void*))
{
	if (curr)
	{
		if (del && curr->content)
			(*del)(curr->content);
		free(curr);
	}
}
