/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:49:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/03 21:45:38 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cubscene.h"

//ERROR MESSAGES
# define SCENE_ERR "Error\n%s\n"
# define SCENE_ERR2 "Error\n%s: %s\n"
# define MAP_ERR "Error\nMAP: %c: %s\n"
# define MAP_ERR2 "Error\nMAP: %s\n"
# define FATAL "Fatal error"
# define NO_SCENE "No argument, expected one file in format [*.cub]"
# define TOO_MAN_ARG "Too many arguments, expected one file in format [*.cub]"
# define INVAL_FILE "Invalid file format, expected [*.cub]"
# define INVAL_ID "Invalid identifier, expected [NO, SO, EA, WE, F, C]"
# define MULTI_ID "Multiple definition"
# define INVAL_DEF "Invalid definition, expected [*.xmp]"
# define INVAL_COLOR "Invalid color format, expected [R,G,B]"
# define INVAL_RANGE "Value out of range, expected [0,255]"

# define INVAL_CHAR "Invalid character"
# define MULTIPLE_SPAWN "Multiple player spawn position characters"

# define MAP_CHARSET " 01NSEW"
# define SPAWN_CHARSET "NSEW"

int	get_scene_textures(int fd, t_cubscene *ptr);
int	set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr);
int	get_scene_map(int fd, t_cubscene *scene);
int	convert_map(t_vector *map, t_cubscene *scene);

#endif //PARSING_H