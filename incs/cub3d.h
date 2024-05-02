#ifndef CUB3D_H
#define CUB3D_H

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
	}		img;
	int	key_state[280];	// 280 is the number of keys in the mlx library
	struct toy
	{
		int		x;
		int		y;
	}		player;
}			t_c3_env;

#endif //CUB3D_H