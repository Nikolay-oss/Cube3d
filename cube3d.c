#include <mlx.h>
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

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
	int i;
	int x;
	int y;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	i = 0;
	while (i < 2000)
	{
		x = (int)2 * sin(i) * 100 + 500;
		y = (int)2 * cos(i) * 100 + 500;
		// x = i;
		// y = (int)sin(i) * 1000 + 500;
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		// my_mlx_pixel_put(&img, x + 1, y + 1, 0x00FF0000);
		// my_mlx_pixel_put(&img, x - 1, y - 1, 0x00FF0000);
		i++;
	}
	i = 0;
	while (i < 600)
	{
		my_mlx_pixel_put(&img, 200 + i, 200, 0x00F00000);
		my_mlx_pixel_put(&img, 800, 200 + i, 0x00FFF000);
		my_mlx_pixel_put(&img, 200 + i, 800, 0x00FFFF00);
		my_mlx_pixel_put(&img, 200, 200 + i, 0x00FF0000);
		i++;
	}
	i = 0;
	while (i < 400)
	{
		my_mlx_pixel_put(&img, 300 + i, 500, 0x00FF0000);
		my_mlx_pixel_put(&img, 500, 300 + i, 0x00FF0000);
		i++;
	}
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}