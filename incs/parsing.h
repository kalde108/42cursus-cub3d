/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:49:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 19:45:52 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cubscene.h"
# include "player.h"

# define IDENTIFIERS 6

//FILE EXTENTIONS
# define CUB_EXT ".cub"
# define XMP_EXT ".xpm"

//ERROR MESSAGES
# define SCENE_ERR "Error\n%s\n"
# define SCENE_ERR2 "Error\n%s: %s\n"
# define MAP_ERR "Error\nMAP: %c: %s\n"
# define MAP_ERR2 "Error\nMAP: %s\n"
# define MLX_ERR "Error\nminilibx: %s: %s\n"
# define FATAL "Fatal"
# define NO_SCENE "No argument, expected one file in format [*.cub]"
# define TOO_MAN_ARG "Too many arguments, expected one file in format [*.cub]"
# define INVAL_FILE "Invalid file format, expected [*.cub]"
# define INVAL_ID "Invalid identifier"
# define MULTI_ID "Multiple definition of identifier"
# define INVAL_PATH "Invalid definition, expected one file in format [*.xmp]"
# define AMBIGUOUS_DEF "Ambiguous definition"
# define INVAL_COLOR "Invalid color format, expected [R],[G],[B] ranging [0,255]"
# define INVAL_RANGE "Color value out of range, expected [0,255]"
# define INVAL_CHAR "Invalid character"
# define NO_SPAWN "Missing player spawn character, expected [N] [S] [E] or [W]"
# define MULTIPLE_SPAWN "Multiple player spawn characters"
# define NON_ENCLOSED "Spawn position not surrounded by walls"

//MAP_CHARSET
# define MAP_CHARSET " 01NSEW"
# define WALL_CHARSET "1"
# define SPAWN_CHARSET "NSEW"
# define ENCLOSURE_CHARSET "1"

int		get_cubscene(char *path, t_cubscene *ptr);
int		get_player_spawn(t_cubscene scene, t_player *player);
int		is_player_enclosed(t_cubscene *scene, t_player *player);
int		get_scene_textures(int fd, t_cubscene *ptr);
int		set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr);
int		get_scene_map(int fd, t_cubscene *scene);
int		convert_map(t_vector *map, t_cubscene *scene);

#endif //PARSING_H