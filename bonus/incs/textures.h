#ifndef TEXTURES_H
# define TEXTURES_H

# include <stdbool.h>
# include <stddef.h>

//ATTRIBUTES
# define DEFAULT_FRAMETIME 100
# define DEFAULT_HINDER 0
# define DEFAULT_ANIMATION LOOP
# define DEFAULT_DAMAGE 0
# define DEFAULT_WALKABLE true

# define ATTR_1 "animation="
# define ATTR_2 "frametime="
# define ATTR_3 "framestart="
# define ATTR_4 "walkable="
# define ATTR_5 "hinder="
# define ATTR_6 "damage="

//ERROR MESSAGES
# define INVAL_ATTR "Invalid attribute"
# define INVAL_ANIMATION "Invalid animation attribute value"

typedef enum e_anim
{
	NONE,
	LOOP,
	SWAY,
	RANDOM
}	t_anim;

typedef struct s_attributes
{
	size_t	frametime;
	t_anim	animation;
	int		damage;
	int		hinder;
	bool	walkable;
}	t_attributes;

typedef struct s_texdata
{
	char	*filepath;
	void	*mlx_img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texdata;

typedef struct s_elem
{
	t_texdata		*frames;
	t_texdata		*current;
	int				n;
	int				current_frame;
	int				dir;
	char			options;
	t_attributes	attr;
}	t_elem;

//ATTRIBUTES
typedef int (*t_set_attr)(char *, char *, t_elem *elem);

int set_frametime_attr(char *identifier, char *str,  t_elem *elem);
int set_animation_attr(char *identifier, char *str,  t_elem *elem);

# define ANIM_NONE "none"
# define ANIM_LOOP "loop"
# define ANIM_SWAY "sway"
# define ANIM_RANDOM "random"

#endif
