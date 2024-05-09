/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:53 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 18:06:00 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_math.h"
# include "cubscene.h"
# include "player.h"

# define WIDTH		2048
# define HEIGHT		1152
# define WIN_NAME	"Cub3D - @kchillon @ibertran"

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
}	t_c3_env;

int		check_arguments(int ac, char **av);
int		init_cubenv(t_c3_env *env, char *arg);
void	destroy_cubenv(t_c3_env *env);
int		open_mlx_window(t_c3_env *env);
int		load_textures(void *mlx_ptr, t_cubscene *scene);

int		render(t_c3_env *env);

#endif //CUB3D_H