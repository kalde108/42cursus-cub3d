/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:47 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 18:38:21 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "key_index.h"

#include <X11/Xutil.h>

int	keydown_hook(int keycode, t_c3_env *env)
{
	int	keyindex;

	if (keycode == XK_Escape)
		mlx_loop_end(env->mlx);
	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
		env->key_state[keyindex] = 1;
	return (0);
}
