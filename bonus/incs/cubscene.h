/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/11 21:18:50 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBSCENE_H
# define CUBSCENE_H

# include <stdint.h>
# include <stddef.h>

# include "ft_math.h"
# include "identifiers.h"
# include "textures.h"

# define IDENTIFIER_FLOOR "FL"
# define IDENTIFIER_CEILING "CE"
# define IDENTIFIER_PORTAL "PO"

# define MAX_TEXTURE 26
# define BASIC_TEXTURE 3
# define SPECIAL_TEXTURES 1

# define MAX_PORTALS 10
# define NO_LINK -1

enum e_textype
{
	WALL,
	FLOOR,
	CEILING,
	PORTAL,
	ENTITY,
	TEXTURES_TYPES
};

typedef struct s_portal
{
	int		id;
	t_v2d_i	pos;
	int		face;
	bool	is_open;
	int		linked_portal;
}	t_portal;

typedef struct s_portals
{
	t_portal	tab[MAX_PORTALS];
	int			total;
	int			opened[2];
	int			opened_count;
}	t_portals;

typedef struct s_cubscene
{
	t_elem		**elems;
	int			*map;
	int			width;
	int			height;
	t_portals	portals;
}	t_cubscene;

void	destroy_scene(t_cubscene *scene, void *mlx_ptr);

#endif //CUBSCENE_H
