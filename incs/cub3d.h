#ifndef CUB3D_H
# define CUB3D_H

# include "ft_math.h"
# include <cubscene.h>

# define WIDTH		2048
# define HEIGHT		1152
// # define WIDTH		1024
// # define HEIGHT		576

typedef struct s_player
{
	t_v2d_d	pos;	// player position
	t_v2d_d	dir;	// player orientation
	t_v2d_d	plane;	// camera plane
	double	mv_speed;
	double	rt_speed;
}	t_player;


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

int		check_scene_format(char **argv);
int		get_cubscene(char *path, t_cubscene *ptr);

int		init_scene(t_cubscene *ptr);
void	init_text(t_tex *img);
void	destroy_scene(t_cubscene *ptr);
int		get_player_spawn(t_cubscene scene, t_player *player);
int		is_player_enclosed(t_cubscene *scene, t_player *player);

int	render(t_c3_env *env);

// a ranger
int	get_color(char type, t_v2d_d ray_dir, int side, double perp_wall_dist);

#endif //CUB3D_H