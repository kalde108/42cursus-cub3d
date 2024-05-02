#ifndef CUB3D_H
#define CUB3D_H

# define WIDTH		1024
# define HEIGHT		576

#define mapWidth 24
#define mapHeight 24

typedef struct s_c3_env
{
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
	double	posX;	// player x position
	double	posY;	// player y position
	double	dirX;	// direction vector's x
	double	dirY;	// direction vector's y
	double	planeX;	// camera plane x
	double	planeY;	// camera plane y
	double	time;
	double	oldTime;
}	t_c3_env;

int	render(t_c3_env *env);

#endif //CUB3D_H