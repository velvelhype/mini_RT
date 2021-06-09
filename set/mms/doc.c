#include "mlx.h"
#include <math.h>

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     main(void)
{
	void    *mlx;
	void    *mlx_win;
	t_data img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 300, 300, "testlinx");
    img.img = mlx_new_image(mlx, 300, 300);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    double r  = 300;
	double x = 200;
	double y  = 200;
	double pi = 0;
	double color = 1000;

	while(x-- == 0)
		my_mlx_pixel_put(&img, x, y, color);

	// double x = 300;
	// double y = 300;
	// double color = 0;
	// while(x++ < 200)
	// 	my_mlx_pixel_put(&img, x, y, color);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}      