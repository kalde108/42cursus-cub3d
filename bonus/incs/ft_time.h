/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:01:07 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 17:01:09 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include <time.h>
# include <sys/time.h>

# define MANUAL_RESET 0
# define AUTO_RESET 1

typedef struct s_timer
{
	size_t		start;
	size_t		delta;
	char		autoreset;
}	t_timer;

size_t	timer_is_over(t_timer *timer);
size_t	get_time(void);
size_t	get_elapsed_time(t_timer *timer);
void	init_timer(t_timer *timer, size_t delta, char autoreset);
void	start_timer(t_timer *timer);

#endif