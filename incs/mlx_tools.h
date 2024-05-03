#ifndef TMP_MLX_H
# define TMP_MLX_H

# include "cub3d.h"

int	ft_mlx_init(t_c3_env *mlx);

void	ft_mlx_free(t_c3_env *mlx);

// hook
int	keydown_hook(int keycode, t_c3_env *mlx);
int	keyup_hook(int keycode, t_c3_env *mlx);

#endif