/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_address.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:02:44 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 19:09:11 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_ADDRESS_H
# define TILE_ADDRESS_H

// 0b0000 0010 0000 0000 0000 0000 0000 0000
# define TYPE_WALL 0x02000000
// 0b0000 0001 0000 0000 0000 0000 0000 0000
# define TYPE_FL_CE 0x01000000
// 0b0000 0100 0000 0000 0000 0000 0000 0000
# define TYPE_PORTAL 0x04000000

# define EMPTY_CELL 0

// 0b0000 1111 0000 0000 0000 0000 0000 0000
# define TYPE_MASK 0x0F000000

// 0b0000 0000 0000 0000 0000 0000 1111 1111
# define WALL_MASK 0x00FF
// 0b0000 0000 0000 0000 0000 0000 0011 1111
# define FLOOR_MASK 0x003F
// 0b0000 0000 0000 0000 0000 1111 1100 0000
# define CEILING_MASK 0x0FC0
// 0b0000 0000 0000 0000 1111 0000 0000 0000
# define PORTAL_MASK 0xF000

# define CEILING_SHIFT 6
# define PORTAL_SHIFT 12

// # define IS_WALL(x) (x & TYPE_WALL)
// # define NOT_WALL(x) ((x & TYPE_MASK) ^ TYPE_WALL)
// # define IS_FL_CE(x) (x & TYPE_FL_CE)
// # define NOT_FL_CE(x) ((x & TYPE_MASK) ^ TYPE_FL_CE)
// # define IS_PORTAL(x) (x & TYPE_PORTAL)
// # define NOT_PORTAL(x) ((x & TYPE_MASK) ^ TYPE_PORTAL)

// # define GET_TYPE(x) ((x & TYPE_MASK))
// # define GET_WALL(x) (x & WALL_MASK)
// # define GET_FLOOR(x) (x & FLOOR_MASK)
// # define GET_CEILING(x) ((x & CEILING_MASK) >> CEILING_SHIFT)
// # define GET_PORTAL(x) ((x & PORTAL_MASK) >> PORTAL_SHIFT)

#endif
