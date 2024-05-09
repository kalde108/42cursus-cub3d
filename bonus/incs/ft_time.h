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

char	timer_is_over(t_timer *timer);
size_t	get_time(void);
size_t	get_elapsed_time(t_timer *timer);
void	init_timer(t_timer *timer, size_t delta, char autoreset);
void	start_timer(t_timer *timer);

#endif