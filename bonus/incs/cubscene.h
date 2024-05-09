/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/09 14:14:04 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBSCENE_H
# define CUBSCENE_H

# include <stdint.h>

# include "ft_vector.h"

// IDENTIFIERS
# define WALL1 "W1"
# define WALL2 "W2"
# define FLOOR "FL"
# define CEILING "CE"

//TEXTURES ARRAY
enum e_textures
{
	W1 = 0,
	W2,
	FL,
	CE,
	TEXTURE_COUNT
};

typedef enum e_identifier
{
	ID_INVAL = -1,
	ID_WALL1,
	ID_WALL2,
	ID_FLOOR,
	ID_CEILING,
	ID_COUNT
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
	t_tex		texture[TEXTURE_COUNT];
	__uint32_t	floor;
	__uint32_t	ceiling;
	char		*map;
	int			width;
	int			height;
}	t_cubscene;

void	destroy_scene(t_cubscene *scene, void *mlx_ptr);

#endif //CUBSCENE_H
