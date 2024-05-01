#include "mlx.h"
#include "tmp_mlx.h"

int	ft_mlx_init()
{
	t_mlx	mlx;

	mlx = (t_mlx){0};
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (1);
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "mlx");
	if (!mlx.win)
		return (1);
	mlx.img.img = mlx_new_image(mlx.mlx, 1920, 1080);
	if (!mlx.img.img)
		return (1);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length, &mlx.img.endian);
	if (!mlx.img.addr)
		return (1);
	return (0);
}
