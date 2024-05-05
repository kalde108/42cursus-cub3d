#ifndef CUBSCENE_H
# define CUBSCENE_H

# include "ft_vector.h"

// IDENTIFIERS
# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define FLOOR "F"
# define CEILING "C"

//TEXTURES ARRAY
# define TEXTURES 4
# define NO 0
# define SO 1
# define EA 2
# define WE 3

typedef enum e_identifier
{
	ID_INVAL = -1,
	ID_NORTH,
	ID_SOUTH,
	ID_EAST,
	ID_WEST,
	ID_FLOOR,
	ID_CEILING
}	t_identifier;

typedef struct s_cubscene_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_cubscene_color;

typedef struct s_tex
{
	char	*filepath;
	void	*ptr;
	int		width;
	int		height;
}	t_tex;

typedef struct s_cubscene
{
	t_tex				texture[TEXTURES];
	t_cubscene_color	floor;
	t_cubscene_color	ceilling;
	char				*map;
	int					width;
	int					height;
}	t_cubscene;

void	destroy_scene(t_cubscene *scene, void *mlx_ptr);

#endif //CUBSCENE_H
