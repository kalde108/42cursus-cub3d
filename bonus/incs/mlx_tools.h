/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 01:30:31 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_TOOLS_H
# define MLX_TOOLS_H

# include "cub3d.h"

// hook
int	keydown_hook(int keycode, t_c3_env *mlx);
int	keyup_hook(int keycode, t_c3_env *mlx);
int buttonpress_hook(int button, int x, int y, t_c3_env *env);
int buttonrelease_hook(int button, int x, int y, t_c3_env *env);
int mousemotion_hook(int x, int y, t_c3_env *env);

#endif //MLX_TOOLS_H
