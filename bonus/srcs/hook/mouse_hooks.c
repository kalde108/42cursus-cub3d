/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:47:54 by kchillon          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:55 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>

#include "mlx.h"
#include "minimap.h"

static void	left_button(void *mlx, void *win, t_mouse *mouse)
{
	if (mouse->status & MOUSE_BUTTON_LEFT)
		mouse->status &= ~MOUSE_BUTTON_LEFT;
	else
		mouse->status |= MOUSE_BUTTON_LEFT;
	mlx_mouse_move(mlx, win, WIDTH >> 1, HEIGHT >> 1);
	mouse->x = WIDTH >> 1;
	mouse->y = HEIGHT >> 1;
	mouse->delta.x = 0;
	if (mouse->status)
		mlx_mouse_hide(mlx, win);
	else
		mlx_mouse_show(mlx, win);
}

static void	right_button(int x, int y, t_mouse *mouse)
{
	if (mouse->status & MOUSE_BUTTON_RIGHT)
		mouse->status &= ~MOUSE_BUTTON_RIGHT;
	else
		mouse->status |= MOUSE_BUTTON_RIGHT;
	mouse->x = x;
	mouse->y = y;
	mouse->delta = (t_v2d_i){0, 0};
}

int	buttonpress_hook(int button, int x, int y, t_c3_env *env)
{
	if (Button1 == button
		&& !(env->mouse.status & MOUSE_BUTTON_RIGHT))
		left_button(env->mlx, env->win, &env->mouse);
	if (Button3 == button
		&& !(env->mouse.status & MOUSE_BUTTON_LEFT)
		&& is_on_minimap(&env->options.minimap, x, y))
		right_button(x, y, &env->mouse);
	return (0);
}

int	buttonrelease_hook(int button, int x, int y, t_c3_env *env)
{
	(void)x;
	(void)y;
	if (Button3 == button && env->mouse.status & MOUSE_BUTTON_RIGHT)
		env->mouse.status &= ~MOUSE_BUTTON_RIGHT;
	return (0);
}
