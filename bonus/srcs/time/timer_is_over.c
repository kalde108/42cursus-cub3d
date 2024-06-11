/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_is_over.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:25 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:55:25 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

size_t	timer_is_over(t_timer *timer)
{
	size_t			current;
	size_t			diff;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	diff = current - timer->start;
	if (diff >= timer->delta)
	{
		if (timer->autoreset)
			timer->start = current - diff % timer->delta;
		return (diff / timer->delta);
	}
	return (0);
}
