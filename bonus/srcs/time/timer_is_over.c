#include "ft_time.h"

char	timer_is_over(t_timer *timer)
{
	size_t	current;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (current - timer->start >= timer->delta)
	{
		if (timer->autoreset)
			timer->start = current;
		return (1);
	}
	return (0);
}
