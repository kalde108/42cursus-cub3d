/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_address.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:02:44 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 21:20:16 by ibertran         ###   ########lyon.fr   */
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

#endif
