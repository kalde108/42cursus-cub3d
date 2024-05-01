/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:49:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/01 05:42:15 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cubscene.h"

//ERROR MESSAGES
# define SCENE_ERR "Error\n%s\n"
# define SCENE_ERR2 "Error\n%s: %s\n"
# define SCENE_ERR3 "Error\n%d,%d,%d: %s\n"
# define FATAL_SCENE "Scene loading failed"
# define NO_SCENE "No scene file supplied, expected [*.cub]"
# define INVAL_FILE "Invalid scene file format, expected [*.cub]"
# define INVAL_ID "Invalid identifier"
# define MULTI_ID "Multiple definition"
# define INVAL_DEF "Invalid definition"
# define INVAL_COLOR "Invalid color"

# define COLOR_INIT -1

int	set_scene_info(char *tok, char *str, t_identifier id, t_cubscene *ptr);

#endif //PARSING_H