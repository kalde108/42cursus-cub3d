/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:49:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/11 15:16:07 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cubscene.h"
# include "player.h"
# include "cub3d.h"

//FILE EXTENTIONS
# define CUB_EXT ".cub"
# define XMP_EXT ".xpm"

//SPRITE TYPES
# define SPRITE_FILE 1
# define SPRITE_DIRECTORY 2

//ERROR MESSAGES
# define SCENE_ERR "Error\n%s\n"
# define SCENE_ERR2 "Error\n%s: %s\n"
# define SCENE_ERR3 "Error\n%s: %s: %s\n"
# define MAP_ERR "Error\nMAP: %c: %s\n"
# define MAP_ERR2 "Error\nMAP: %s\n"
# define MLX_ERR "Error\nminilibx: %s: %s\n"
# define MLX_ERR2 "Error\nminilibx: %s\n"
# define FATAL "Fatal"
# define NO_SCENE "No argument, expected one file in format [*.cub]"
# define TOO_MAN_ARG "Too many arguments, expected one file in format [*.cub]"
# define INVAL_FILE "Invalid file format, expected [*.cub]"
# define INVAL_ID "Invalid identifier"
# define MULTI_ID "Multiple definition of identifier"
# define INVAL_PATH "Invalid definition, expected one file in format [*.xmp] or a directory"
# define INVAL_COLOR "Invalid color format, expected [R,G,B] ranging [0,255]"
# define INVAL_RANGE "Color value out of range, expected [0,255]"
# define INVAL_CHAR "Invalid character"
# define NO_PLAYER "Missing player spawn character, expected [N] [S] [E] or [W]"
# define MULTIPLE_PLAYER "Multiple player spawn characters"
# define NO_MONSTER "Missing monster spawn character, expected [M]"
# define MULTIPLE_MONSTER "Multiple monster spawn characters"
# define NON_ENCLOSED "Spawn position not surrounded by walls"

//MAP_CHARSET
# define MAP_SPECIALS_CHARSET "NSEWPM"

# define SPAWN_CHARSET "NSEW"
# define ENCLOSURE_CHARSET "12"
# define UNCLOSED_CHARSET " "

# define MONSTER_CHAR 'M'

enum e_maplayer
{
	MAP_LAYER,
	FLOOR_LAYER,
	CEILING_LAYER,
	LAYERS_COUNT
};

int		get_cubscene(char *path, t_c3_env *env);
int		get_player_spawn(t_vector *map, t_entity *player);
int		is_player_enclosed(t_cubscene *scene, t_entity *player);
int		get_scene_textures(int fd, t_cubscene *ptr);
int		set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr);
int		get_scene_map(int fd, t_c3_env *env);
int		get_entities(t_vector *map, t_c3_env *env);
int		convert_map(t_vector *map, t_cubscene *scene);
char	*get_map_charset(t_tex *textures);
char	*get_layer_charset(t_tex *textures);
int		get_monster_spawn(t_vector *map, t_entity *monster);

#endif //PARSING_H