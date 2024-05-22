/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/22 21:43:21 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

// # include <time.h>
# include <pthread.h>

# include "cubscene.h"
# include "player.h"
# include "entity.h"
# include "ft_time.h"
# include "key_index.h"
# include "stdbool.h"

# define WIDTH		2048
# define HEIGHT		1152
// # define WIDTH		4096
// # define HEIGHT		2304
# define WIN_NAME	"Cub3D - @kchillon @ibertran"

# define FOV		90.0

# ifndef CPUCORES
#  define CPUCORES	1
# endif

# define ENTITY_LIMIT	100

// # define FRAME_TIME	0.008333333333333333	// 120 fps
# define FRAME_TIME	0.016666666666666666	// 60 fps
// # define FRAME_TIME	0.03333333333333333		// 30 fps

# define WIDTH_LOG2	11
// # define WIDTH_LOG2	12

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_mouse
{
	bool	status;
	int		x;
	int		y;
	int		delta;
}	t_mouse;

typedef struct s_c3_env
{
	t_cubscene		scene;
	void			*mlx;
	void			*win;
	t_img			img;
	int				key_state[KEY_COUNT];
	t_player		player;	// group in struct
	t_entity		monster;	// group in struct
	double			frame_time;
	pthread_mutex_t	call_mutex;
	double			z_buffer[WIDTH];	// group in struct
	t_entity		entities[ENTITY_LIMIT];	// group in struct
	size_t			entity_count;	// group in struct
	struct clocks
	{
		t_timer		frame_timer;
		t_timer		map_tex_timer;
	}				clocks;
	t_mouse			mouse;
}	t_c3_env;

int		check_arguments(int ac, char **av);
int		init_cubenv(t_c3_env *env, char *arg);
void	destroy_cubenv(t_c3_env *env);
int		open_mlx_window(t_c3_env *env);
int		load_textures(void *mlx_ptr, t_elem **textures);

int		render(t_c3_env *env);

#endif //CUB3D_H

/*

char
00000000

type
11XXXXXX

wall address
00XXXXXX

empty address
01XXXXXX

portal address
10XXXXXX

wall id
XX111111

floor id
XXXXX111

ceiling id
XX111XXX

portal id
XX111111


short
00000000 00000000

type
1111XXXX XXXXXXXX

wall address
0000XXXX XXXXXXXX

not wall address
0001XXXX XXXXXXXX

wall id
XXXXXXXX 11111111

floor id
XXXXXXXX XXXX1111

ceiling id
XXXXXXXX 1111XXXX


int
00000000 00000000 00000000 00000000

*/