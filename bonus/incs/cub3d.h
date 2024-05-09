/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/09 19:36:31 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

// # include <time.h>

# include "ft_math.h"
# include "cubscene.h"
# include "player.h"
# include "ft_time.h"

# define WIDTH		2048
# define HEIGHT		1152
# define WIN_NAME	"Cub3D - @kchillon @ibertran"

# define FRAME_TIME	0.016666666666666666
// # define FRAME_TIME	0.03333333333333333

# define WIDTH_LOG2	11

// # define GROUND_CHARSET "0FC"

# define WALL_CHARSET "12"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_c3_env
{
	t_cubscene	scene;
	void		*mlx;
	void		*win;
	t_img		img;
	int			key_state[280];	// arbitrary size (number of keys to handle)
	t_player	player;
	t_timer		frame_timer;
	double		frame_time;
	// size_t		time;
	// size_t		old_time;
}	t_c3_env;

int		check_arguments(int ac, char **av);
int		init_cubenv(t_c3_env *env, char *arg);
void	destroy_cubenv(t_c3_env *env);
int		open_mlx_window(t_c3_env *env);
int		load_textures(void *mlx_ptr, t_cubscene *scene);

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