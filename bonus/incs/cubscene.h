/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/10 23:34:20 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBSCENE_H
# define CUBSCENE_H

# include <stdint.h>

# include "ft_vector.h"
# include "identifiers.h"

# define IDENTIFIER_FLOOR "FL"
# define IDENTIFIER_CEILING "CE"
# define IDENTIFIER_PORTAL "PO"

# define MAX_TEXTURE 26
# define BASIC_TEXTURE 3

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

typedef struct s_tex
{
	t_texdata	*sprite;
	int			n;
}	t_tex;

typedef struct s_cubscene
{
	t_tex		**texture;
	short		*map;
	int			width;
	int			height;
}	t_cubscene;

void	destroy_scene(t_cubscene *scene, void *mlx_ptr);

#endif //CUBSCENE_H
