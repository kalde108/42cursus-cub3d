/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/07 22:53:13 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "key_index.h"

int	keyup_hook(int keycode, t_c3_env *env)
{
	int	keyindex;

	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
		env->key_state[keyindex] = 0;
	return (0);
}
