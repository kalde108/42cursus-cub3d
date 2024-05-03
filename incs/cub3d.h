#ifndef CUB3D_H
# define CUB3D_H

# include <cubscene.h>

int		check_scene_format(char **argv);
int		get_cubscene(char *path, t_cubscene *ptr);

int		init_scene(t_cubscene *ptr);
void	destroy_scene(t_cubscene *ptr);

# define WIDTH		2048
# define HEIGHT		1152
// # define WIDTH		1024
// # define HEIGHT		576

#define mapWidth 24
#define mapHeight 24

extern char	**test_map;

typedef struct s_v2d_d
{
	double	x;
	double	y;
}	t_v2d_d;

typedef struct s_v2d_i
{
	int	x;
	int	y;
}	t_v2d_i;

// typedef struct s_vertex
// {
// 	t_vector_2d	pos;
// 	t_vector_2d	dir;
// }	t_vertex;

typedef struct s_c3_env
{
	t_cubscene	scene;
	void	*mlx;
	void	*win;
	struct s_img
	{
		void	*img;
		char	*addr;
		int		bits_per_pixel;
		int		line_length;
		int		endian;
	}	img;
	int	key_state[280];	// arbitrary size (number of keys to handle)
	t_v2d_d	pos;	// player position
	t_v2d_d	dir;	// player direction
	t_v2d_d	plane;	// camera plane
	double	move_speed;
	double	rot_speed;
}	t_c3_env;

int	render(t_c3_env *env);

// a ranger
int	get_color(int type, t_v2d_d ray_dir, int side, double perp_wall_dist);

#endif //CUB3D_H