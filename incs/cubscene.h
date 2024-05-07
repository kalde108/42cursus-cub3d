/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:50:47 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBSCENE_H
# define CUBSCENE_H

# include <stdint.h>

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

typedef struct s_tex
{
	char	*filepath;
	void	*mlx_img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_tex;

typedef struct s_cubscene
{
	t_tex		texture[TEXTURES];
	__uint32_t	floor;
	__uint32_t	ceiling;
	char		*map;
	int			width;
	int			height;
}	t_cubscene;

void	destroy_scene(t_cubscene *scene, void *mlx_ptr);

#endif //CUBSCENE_H
