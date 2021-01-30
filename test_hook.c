#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef	struct	s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
}				t_vars;

int				key_hook(int keycode)//, t_vars *vars)
{
	// printf("%p\n", vars->mlx);
	printf("keycode:\t%d\n", keycode);
	return (keycode);
}

int             win_close(t_vars *vars) // int keycode, 
{
    mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int			draw_circle(t_data *img)
{
	int i;
	int x;
	int y;

	// printf("keycode:\t%d\n", keycode);
	// if (keycode != 8)
	// 	return (0);
	i = 0;
	while (i < 2000)
	{
		x = (int)2 * sin(i) * 100 + 500;
		y = (int)2 * cos(i) * 100 + 500;
		// x = i;
		// y = (int)sin(i) * 1000 + 500;
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		// my_mlx_pixel_put(&img, x + 1, y + 1, 0x00FF0000);
		// my_mlx_pixel_put(&img, x - 1, y - 1, 0x00FF0000);
		i++;
	}
	return (0);
}

int				win_close_esc(int keycode, t_vars *vars)
{
	if (keycode == 8)
		draw_circle(vars->img);
	return (keycode == 53 ? win_close(vars) : 0);
}

int				render_frame(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

void			create_image(t_data *img, t_vars *vars)
{
	// int i;
	// int x;
	// int y;


	img->img = mlx_new_image(vars->mlx, 1920, 1080);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
                                 &img->endian);
	// i = 0;
	// while (i < 2000)
	// {
	// 	x = (int)2 * sin(i) * 100 + 500;
	// 	y = (int)2 * cos(i) * 100 + 500;
	// 	// x = i;
	// 	// y = (int)sin(i) * 1000 + 500;
	// 	my_mlx_pixel_put(img, x, y, 0x00FF0000);
	// 	// my_mlx_pixel_put(&img, x + 1, y + 1, 0x00FF0000);
	// 	// my_mlx_pixel_put(&img, x - 1, y - 1, 0x00FF0000);
	// 	i++;
	// }
	// i = 0;
	// while (i < 600)
	// {
	// 	my_mlx_pixel_put(img, 200 + i, 200, 0x00FF0000);
	// 	my_mlx_pixel_put(img, 800, 200 + i, 0x00FF0000);
	// 	my_mlx_pixel_put(img, 200 + i, 800, 0x00FF0000);
	// 	my_mlx_pixel_put(img, 200, 200 + i, 0x00FF0000);
	// 	i++;
	// }
	// i = 0;
	// while (i < 400)
	// {
	// 	my_mlx_pixel_put(img, 300 + i, 500, 0x00FF0000);
	// 	my_mlx_pixel_put(img, 500, 300 + i, 0x00FF0000);
	// 	i++;
	// }
	// draw_circle(img);
}

int             main(void)
{
    // void    *mlx;
    // void    *mlx_win;
    t_data  img;
	t_vars	vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");

	// draw image
    create_image(&img, &vars);
	vars.img = &img;
	
	// check keyhook
	// mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, &win_close_esc, &vars);
	mlx_hook(vars.win, 17, 0, &win_close, &vars);
	// mlx_hook(vars.win, 2, 0, &draw_circle, &img);
	// mlx_mouse_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, &render_frame, &vars);
    mlx_loop(vars.mlx);
}