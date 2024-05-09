# include "ft_time.h"

void	start_timer(t_timer *timer)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	timer->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
