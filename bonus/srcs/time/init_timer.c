/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_timer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:12 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:55:12 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

void	init_timer(t_timer *timer, size_t delta, char autoreset)
{
	struct timeval	tv;

	timer->delta = delta;
	timer->autoreset = autoreset;
	if (timer->autoreset)
	{
		gettimeofday(&tv, NULL);
		timer->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	else
		timer->start = 0;
}
