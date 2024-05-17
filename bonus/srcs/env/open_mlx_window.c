/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_mlx_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:17 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 18:34:12 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <unistd.h>
#include <math.h>

#include "libft.h"
#include "mlx.h"
#include "mlx_tools.h"
#include "parsing.h"
#include "cubdef.h"

static void	setup_mlx_hooks(t_c3_env *env);

int	open_mlx_window(t_c3_env *env)
{
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, WIN_NAME);
	if (!env->win)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->img.addr = mlx_get_data_addr(env->img.img,
			&env->img.bits_per_pixel,
			&env->img.line_length,
			&env->img.endian);
	if (!env->img.addr)
	{
		ft_dprintf(STDERR_FILENO, MLX_ERR2, FATAL);
		return (1);
	}
	env->img.line_length = log2(env->img.line_length);
	setup_mlx_hooks(env);
	return (0);
}

static void	setup_mlx_hooks(t_c3_env *env)
{
	mlx_hook(env->win, 
		DestroyNotify, StructureNotifyMask, &mlx_loop_end, env->mlx);
	mlx_hook(env->win, 
		KeyPress, KeyPressMask, &keydown_hook, env);
	mlx_hook(env->win, 
		KeyRelease, KeyReleaseMask, &keyup_hook, env);
	mlx_hook(env->win, 
		ButtonPress, ButtonPressMask, &buttonpress_hook, env);
	mlx_hook(env->win, 
		FocusOut, FocusChangeMask, &focusout_hook, env);
	mlx_loop_hook(env->mlx, &render, env);
}
