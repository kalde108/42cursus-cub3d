/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:20 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:55:20 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

void	start_timer(t_timer *timer)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	timer->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
