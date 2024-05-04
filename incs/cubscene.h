#ifndef SCENE_H
# define SCENE_H

# include "ft_vector.h"

// IDENTIFIERS
# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define FLOOR "F"
# define CEILING "C"

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

typedef struct s_img
{
	char	*filepath;
	void	*ptr;
	int		width;
	int		height;
}	t_img;

typedef struct s_cubscene_textures
{
	t_img	so;
	t_img	no;
	t_img	ea;
	t_img	we;
}	t_cubscene_textures;

typedef struct s_cubscene
{
	t_cubscene_textures	texture;
	t_cubscene_color	floor;
	t_cubscene_color	ceilling;
	// t_vector			map;
	char				*map;
	int					width;
	int					height;
}	t_cubscene;

#endif //SCENE_H
