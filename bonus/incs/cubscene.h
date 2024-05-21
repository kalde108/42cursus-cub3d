/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/21 16:19:29 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBSCENE_H
# define CUBSCENE_H

# include <stdint.h>
# include <stddef.h>

# include "ft_math.h"
# include "identifiers.h"
# include "stdbool.h"

# define IDENTIFIER_FLOOR "FL"
# define IDENTIFIER_CEILING "CE"
# define IDENTIFIER_PORTAL "PO"

# define MAX_TEXTURE 26
# define BASIC_TEXTURE 3
# define SPECIAL_TEXTURES 1

enum e_textype
{
	WALL,
	FLOOR,
	CEILING,
	PORTAL,
	ENTITY,
	TEXTURES_TYPES
};

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
	t_texdata	*frames;
	t_texdata	*current;
	int			n;
	int			current_frame;
	int			dir;
	char		options;
	struct
	{
		size_t	frametime;
		int		animation;
		int		dps;
		int		hinder;
		bool	walkable;
	}			attr;
}	t_elem;

# define MAX_PORTALS 10
typedef struct s_portal	// A DEPLACER
{
	int		id;
	t_v2d_i	pos;
	int		is_open;
	int		linked_portal;
}	t_portal;

typedef struct s_cubscene
{
	t_elem		**elems;
	int			*map;
	int			width;
	int			height;
	struct s_portals
	{
		t_portal	tab[MAX_PORTALS];
		int			total;
		int			opened[2];
		int			opened_count;
	}			portals;
}	t_cubscene;

void	destroy_scene(t_cubscene *scene, void *mlx_ptr);

#endif //CUBSCENE_H
