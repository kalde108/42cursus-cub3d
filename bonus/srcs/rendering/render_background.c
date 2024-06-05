
#include "cub3d.h"
#include "raycasting.h"

void	background_row(t_c3_env *env, int y, t_elem **textures);

static void	draw_backgound_chunk(t_c3_env *env, int start, int end)
{
	int		y;

	y = start;
	while (y < end)
	{
		background_row(env, y, env->scene.elems);
		y++;
	}
}

void	*draw_backgound_thread(void *arg)
{
	static int	call = 0;
	t_c3_env	*env;
	int			start;
	int			end;

	env = (t_c3_env *)arg;
	pthread_mutex_lock(&env->call_mutex);
	call++;
	call = call % CPUCORES;
	start = call * ((HEIGHT >> 1) / CPUCORES) + (HEIGHT >> 1);
	end = (call + 1) * ((HEIGHT >> 1) / CPUCORES) + (HEIGHT >> 1);
	pthread_mutex_unlock(&env->call_mutex);
	draw_backgound_chunk(env, start, end);
	return (NULL);
}

int	render_backgound(t_c3_env *env)
{
	pthread_t	threads[CPUCORES];
	int			i;
	int			err;

	err = 0;
	i = 0;
	while (i < CPUCORES)
	{
		err = pthread_create(&threads[i], NULL, draw_backgound_thread, env);
		if (err)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	return (err);
}
