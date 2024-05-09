#include "ft_time.h"

size_t	get_elapsed_time(t_timer *timer)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000) - timer->start);
}
