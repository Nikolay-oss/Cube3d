#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

typedef	struct	s_player
{
	int		x;
	int		y;
	t_data	*img;
}				t_player;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             win_close(t_vars *vars) // int keycode, 
{
    mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

// int			get_key(int keycode)
// {
// 	printf("key:\t%d\n", keycode);
// 	return (0);
// }

int			draw_circle(t_player *player)
{
	int i;
	int x;
	int y;

	i = 0;
	while (i < 2000)
	{
		x = (int)2 * sin(i) * 100 + player->x;
		y = (int)2 * cos(i) * 100 + player->y;
		my_mlx_pixel_put(player->img, x, y, 0x00FF0000);
		i++;
	}
	return (0);
}

void		img_clear(t_player *player)
{
	int i;
	int x;
	int y;

	i = 0;
	while (i < 2000)
	{
		x = (int)2 * sin(i) * 100 + player->x;
		y = (int)2 * cos(i) * 100 + player->y;
		my_mlx_pixel_put(player->img, x, y, 0x00000000);
		i++;
	}
}

int			render_frame(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int			shift_circle(int keycode, t_player *player)
{
	int step;

	step = 20;
	img_clear(player);
	if (keycode == 13)
		player->y -= step;
	else if (keycode == 0)
		player->x -= step;
	else if (keycode == 1)
		player->y += step;
	else if (keycode == 2)
		player->x += step;
	draw_circle(player);
	return (0);
}

int	main()
{
	t_data img;
	t_vars vars;
	t_player player;

	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	vars.img = &img;
	player.x = 500;
	player.y = 500;
	player.img = &img;
	draw_circle(&player);
	mlx_hook(vars.win, 17, 0, &win_close, &vars);
	mlx_hook(vars.win, 2, 1L<<0, &shift_circle, &player);
	mlx_loop_hook(vars.mlx, &render_frame, &vars);
	mlx_loop(vars.mlx);
}
