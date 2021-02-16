#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
// #include "get_next_line.h"
// #include "libft.h"

#define	width	640
#define	height	480

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
	// t_data	*img;
}				t_vars;

typedef	struct	s_game
{
	int		x;
	int		y;
	t_data	img;
	t_vars	vars;
}				t_game;

// typedef	struct	s_player
// {
// 	int		x;
// 	int		y;
// 	t_data	*img;
// 	t_vars	*vars;
// }				t_player;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             win_close(t_game *game) // int keycode, 
{
    mlx_destroy_window(game->vars.mlx, game->vars.win);
	exit(1);
	return (0);
}

int				win_close_esc(int keycode, t_game *game)
{
	// if (keycode == 8)
	// 	draw_circle(vars->img);
	return (keycode == 53 ? win_close(game) : 0);
}

// int			get_key(int keycode)
// {
// 	printf("key:\t%d\n", keycode);
// 	return (0);
// }

// int			draw_circle(t_player *player)
// {
// 	double i;
// 	int x;
// 	int y;

// 	i = 0;
// 	while (i < 2000.0)
// 	{
// 		x = (int)(2 * sin(i) * 100 + player->x);
// 		y = (int)(2 * cos(i) * 100 + player->y);
// 		my_mlx_pixel_put(player->img, x, y, 0x00FF0000);
// 		i += 0.1;
// 	}
// 	return (0);
// }

// void		img_clear(t_player *player)
// {
// 	double i;
// 	int x;
// 	int y;

// 	i = 0;
// 	while (i < 2000.0)
// 	{
// 		x = (int)(2 * sin(i) * 100 + player->x);
// 		y = (int)(2 * cos(i) * 100 + player->y);
// 		my_mlx_pixel_put(player->img, x, y, 0x00000000);
// 		i += 0.1;
// 	}
// }

// int			render_frame(t_game *game)
// {
// 	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
// 	return (0);
// }

// int			shift_circle(int keycode, t_player *player)
// {
// 	int step;

// 	if (keycode == 53)
// 	{
// 		win_close(player->vars);
// 		// mlx_destroy_image(player->vars->mlx, player->vars->img);
// 		return (0);
// 	}
// 	step = 20;
// 	img_clear(player);
// 	if (keycode == 13)
// 		player->y -= step;
// 	else if (keycode == 0)
// 		player->x -= step;
// 	else if (keycode == 1)
// 		player->y += step;
// 	else if (keycode == 2)
// 		player->x += step;
// 	draw_circle(player);
// 	return (0);
// }


// void		draw_vertline(int x, int start, int end, t_game *game)
// {
// 	int i;

// 	i = start;
// 	while (i < end)
// 	{
// 		my_mlx_pixel_put(&game->img, x, i, 0x750000FF);
// 		i++;
// 	}
// }

void		draw_square(t_game *game)
{
	int x;
	int y;
	int i;
	int j;

	x = game->x;
	y = game->y;
	i = x;
	while (i < x + 40)
	{
		j = y;
		while (j < y + 40)
		{
			my_mlx_pixel_put(&game->img, i, j, 0x750000FF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	// mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
}

void		clear_square(t_game *game)
{
	int x;
	int y;
	int i;
	int j;

	x = game->x;
	y = game->y;
	i = x;
	while (i < x + 40)
	{
		j = y;
		while (j < y + 40)
		{
			my_mlx_pixel_put(&game->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	// mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
}

void		shift_item(int keycode, t_game *game)
{
	int step;

	step = 20;
	clear_square(game);
	if (keycode == 13 && game->y != 0)
		game->y -= step;
	else if (keycode == 0 && game->x != 0)
		game->x -= step;
	else if (keycode == 1 && game->y + 2 * step != height)
		game->y += step;
	else if (keycode == 2 && game->x + 2 * step != width)
		game->x += step;
	draw_square(game);
	printf("key -> %d\n", keycode);
}

int			choice_key(int keycode, t_game *game)
{
	win_close_esc(keycode, game);
	shift_item(keycode, game);
	return (0);
}

int	main()
{
	t_game	game;

	game.x = 300;
	game.y = 220;

	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, width, height, "Game");
	game.img.img = mlx_new_image(game.vars.mlx, width, height);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
                                 &game.img.endian);

	draw_square(&game);

	mlx_hook(game.vars.win, 17, 0, &win_close, &game);
	mlx_hook(game.vars.win, 2, 0, &choice_key, &game);
	// mlx_loop_hook(game.vars.mlx, &render_frame, &game);
	mlx_loop(game.vars.mlx);

	// t_data img;
	// t_vars vars;
	// t_player player;

	// vars.mlx = mlx_init();
    // vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	// img.img = mlx_new_image(vars.mlx, 1920, 1080);
    // img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                //  &img.endian);
	// vars.img = &img;
	// player.vars = &vars;
	// player.x = 500;
	// player.y = 500;
	// player.img = &img;
	// draw_circle(&player);
	// mlx_hook(vars.win, 17, 0, &win_close, &vars);
	// mlx_hook(vars.win, 2, 0, &shift_circle, &player);
	// mlx_loop_hook(vars.mlx, &render_frame, &vars);
	// mlx_loop(vars.mlx);
}
