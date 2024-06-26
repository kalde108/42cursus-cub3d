/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:23 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:56:24 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "player.h"

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->camera.dir.x;
	player->camera.dir.x = player->camera.dir.x * cos(angle) \
						- player->camera.dir.y * sin(angle);
	player->camera.dir.y = old_dir_x * sin(angle) \
							+ player->camera.dir.y * cos(angle);
	old_plane_x = player->camera.plane.x;
	player->camera.plane.x = player->camera.plane.x * cos(angle) \
							- player->camera.plane.y * sin(angle);
	player->camera.plane.y = old_plane_x * sin(angle) + \
							player->camera.plane.y * cos(angle);
}
