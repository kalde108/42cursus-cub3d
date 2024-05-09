/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/08 19:23:11 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_TOOLS_H
# define MLX_TOOLS_H

# include "cub3d.h"

//HOOKS
int	keydown_hook(int keycode, t_c3_env *mlx);
int	keyup_hook(int keycode, t_c3_env *mlx);

#endif //MLX_TOOLS_H
