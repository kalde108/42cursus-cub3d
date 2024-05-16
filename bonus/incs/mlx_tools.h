/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:51 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 15:52:55 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_TOOLS_H
# define MLX_TOOLS_H

# include "cub3d.h"

// hook
int	keydown_hook(int keycode, t_c3_env *mlx);
int	keyup_hook(int keycode, t_c3_env *mlx);
int buttonpress_hook(int button, int x, int y, t_c3_env *env);
int	focusout_hook(t_c3_env *env);
int	keydown_hook(int keycode, t_c3_env *mlx);
int	keyup_hook(int keycode, t_c3_env *mlx);

#endif //MLX_TOOLS_H
