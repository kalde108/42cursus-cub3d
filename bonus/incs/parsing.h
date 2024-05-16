/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:49:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 22:31:07 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cubscene.h"
# include "player.h"
# include "entity.h"
# include "cub3d.h"

//FILE EXTENTIONS
# define CUB_EXT ".cub"
# define XMP_EXT ".xpm"

//SPRITE TYPES
# define TEXTURE_FILE 1
# define TEXTURE_DIRECTORY 2

//ERROR MESSAGES
# define NO_SCENE "No argument, expected one file in format [*.cub]"
# define TOO_MAN_ARG "Too many arguments, expected one file in format [*.cub]"
# define INVAL_FILE "Invalid file format, expected [*.cub]"
# define INVAL_ID "Invalid identifier"
# define MULTI_ID "Multiple definition of identifier"
# define INVAL_PATH "Invalid definition, expected one file in format [*.xmp] or a directory"
# define MISSING_PATH "Missing definition, expected one file in format [*.xmp] or a directory"
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

# define WALKABLE -51
# define MISSING -97

enum e_maplayer
{
	MAP_LAYER,
	FLOOR_LAYER,
	CEILING_LAYER,
	LAYERS_COUNT
};

int		get_cubscene(char *path, t_c3_env *env);
int		get_player_spawn(t_vector *map, t_player *player);
int		is_player_enclosed(t_vector *map, t_c3_env *env);
int		get_scene_textures(int fd, t_cubscene *ptr);
int		set_texture(char *tok, char *str, t_identifier id, t_cubscene *ptr);
int		get_scene_map(int fd, t_c3_env *env);
int		get_entities(t_vector *map, t_c3_env *env);
int		convert_map(t_vector map[LAYERS_COUNT], t_cubscene *scene);
char	*get_map_charset(t_elem *textures);
char	*get_layer_charset(t_elem *textures);
int		get_monster_spawn(t_vector *map, t_entity *monster);
int		get_cell_value(t_vector map[LAYERS_COUNT], int y, int x, short *cell);
int		get_directory_textures(char *dirpath, t_elem *texture);
void	init_attributes(t_attributes *ptr);
int		get_attributes(char *identifier, t_elem *elem);

#endif //PARSING_H