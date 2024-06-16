/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:59:01 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/16 16:37:36 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <pthread.h>

# include "cubdef.h"
# include "key_index.h"
# include "raycasting.h"

typedef struct s_img
{
	void	*img;
	t_color	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_mouse
{
	int		status;
	int		x;
	int		y;
	t_v2d_i	delta;
}	t_mouse;

typedef struct s_minimap
{
	bool		enable;
	bool		lock;
	bool		view;
	t_v2d_i		pos;
	int			size;
	double		zoom;
}	t_minimap;

typedef struct s_c3_env
{
	t_cubscene		scene;
	void			*mlx;
	void			*win;
	t_img			img;
	struct s_option
	{
		t_minimap	minimap;
		bool		fps;
	}	options;
	int				key_state[KEY_COUNT];
	t_mouse			mouse;
	t_player		player;
	pthread_mutex_t	call_mutex;
	double			z_buffer[WIDTH];
	size_t			frame_time;
	t_timer			frame_timer;
	t_hit_buffer	**buffer;
}	t_c3_env;

int		check_arguments(int ac, char **av);
int		init_cubenv(t_c3_env *env, char *arg);
int		init_hit_buffer(t_c3_env *env);
void	destroy_cubenv(t_c3_env *env);
int		open_mlx_window(t_c3_env *env);
int		load_textures(void *mlx_ptr, t_elem **textures);

int		render(t_c3_env *env);

#endif //CUB3D_H
