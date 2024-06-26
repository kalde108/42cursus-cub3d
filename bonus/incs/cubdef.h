/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubdef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:21:27 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/16 16:39:49 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBDEF_H
# define CUBDEF_H

# define WIN_NAME	"Cub3D - @kchillon @ibertran"

# ifdef RES_4K
// 4K RESOLUTION
#  define WIDTH			4096
#  define HEIGHT		2304
#  define WIDTH_LOG2	12
# else
// 2K RESOLUTION
#  define WIDTH			2048
#  define HEIGHT		1152
#  define WIDTH_LOG2	11
# endif

# ifndef CPUCORES
#  define CPUCORES	1
# endif

// # define FRAME_TIME	0.008333333333333333	// 120 fps
# define FRAME_TIME	0.016666666666666666		// 60 fps
// # define FRAME_TIME	0.03333333333333333		// 30 fps

# define FOV		90.0
# define FPS_BUFFER 20

//ERROR MESSAGES
# define SCENE_ERR 	"Error\n%s\n"
# define SCENE_ERR2 "Error\n%s: %s\n"
# define SCENE_ERR3 "Error\n%s: %s: %s\n"
# define MAP_ERR 	"Error\nMAP: %c: %s\n"
# define MAP_ERR2 	"Error\nMAP: %s\n"
# define MLX_ERR 	"Error\nminilibx: %s: %s\n"
# define MLX_ERR2 	"Error\nminilibx: %s\n"
# define HITBUF_ERR "Error\nHit buffer: %s: %s\n"
# define FATAL 		"Fatal"

#endif //CUBDEF_H