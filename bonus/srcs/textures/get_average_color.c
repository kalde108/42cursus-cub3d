/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_average_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:41:58 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:41:59 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "color.h"

t_color	get_average_color(t_color *addr, int size)
{
	t_color	*dst;
	t_color	color;
	size_t	r;
	size_t	g;
	size_t	b;

	r = 0;
	g = 0;
	b = 0;
	dst = addr + size;
	while (addr < dst)
	{
		color = *addr;
		r += color.r;
		g += color.g;
		b += color.b;
		addr++;
	}
	color.r = r / (size);
	color.g = g / (size);
	color.b = b / (size);
	return (color);
}
