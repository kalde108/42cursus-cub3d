/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:17:02 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/08 16:24:34 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cubdef.h"
#include "mlx.h"

#include <stdio.h>

static int	get_average_fps(size_t frame_time);

void display_fps(t_c3_env *env)
{
	char	buffer[17];

	if (-1 != sprintf(buffer, "FPS: %3d", get_average_fps(env->frame_time)))
		mlx_string_put(env->mlx, env->win, 10, 20, 0x00FFFFFF, buffer);
}

static int	get_average_fps(size_t frame_time)
{
	static size_t	fps[FPS_BUFFER] = {0};
	static int		i = 0;
	double			average;
	int				j;

	fps[i++] = frame_time;
	if (i == FPS_BUFFER)
	{
		i = 0;
	}
	j = 0;
	average = 0;
	while (j < FPS_BUFFER)
	{
		average += fps[j++];
	}
	average /= FPS_BUFFER;
	if (0 == average)
		return (0);
	return (1000 / average);
}
