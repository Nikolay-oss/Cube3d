#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define	width	1280
#define	height	1024
#define mapWidth 24
#define mapHeight 24

#define	PSQUARE 30
#define OFFSET	200

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef	struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef	struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef	struct	s_plr
{
	t_point	pos;
	t_point	dir;
	int		update;
}				t_plr;

typedef	struct	s_game
{
	t_data	img;
	t_vars	vars;
	t_plr	plr;
	double	origin_angle;
}				t_game;

int		win_close(t_game *game)
{
	mlx_destroy_image(game->vars.mlx, game->img.img);
	mlx_destroy_window(game->vars.mlx, game->vars.win);
	exit(1);
	return (0);
}

void	pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_dir(t_game *game, int color)
{
	int x;
	int y;
	int e_x;
	int e_y;
	int s_x;
	int s_y;
	double k;

	s_x = OFFSET + game->plr.pos.x * PSQUARE;
	s_y = OFFSET + game->plr.pos.y * PSQUARE;;
	e_x = OFFSET + (game->plr.pos.x + game->plr.dir.x) * PSQUARE;
	e_y = OFFSET + (game->plr.pos.y + game->plr.dir.y) * PSQUARE;
	x = s_x;
	y = s_y;
	k = 0.05;
	while (k <= 5)
	{
		x = (s_x + k * e_x) / (1 + k);
		y = (s_y + k * e_y) / (1 + k);
		pixel_put(&game->img, x, y, color);
		// printf("x -> %d\ty -> %d\n", x, y);
		k += 0.05;
	}
}

void	draw_rectangle(t_game *game, int s_x, int s_y, int color, int size)
{
	int	x;
	int	y;

	y = s_y;
	while (y < s_y + size)
	{
		x = s_x;
		while (x < s_x + size)
		{
			pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	x = 0;
	draw_y = OFFSET;
	while (x < mapWidth)
	{
		y = 0;
		draw_x = OFFSET;
		while (y < mapHeight)
		{
			if (worldMap[x][y])
				draw_rectangle(game, draw_x, draw_y, 0x00FFFFFF, PSQUARE);
			draw_x += PSQUARE;
			y++;
		}
		draw_y += PSQUARE;
		x++;
	}
}

void	draw_plr(t_game *game)
{
	int	x = OFFSET + game->plr.pos.x * PSQUARE;
	int y = OFFSET + game->plr.pos.y * PSQUARE;
	draw_rectangle(game, x - 5, y - 5, 0x0000FF00, 10);
}

// void	raycaster(t_game *game)
// {

// }

int		render_frame(t_game *game)
{
	if (game->plr.update)
	{
		game->img.img = mlx_new_image(game->vars.mlx, width, height);
		game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
		// draw fun
		draw_map(game);
		draw_plr(game);
		draw_dir(game, 0x00FF0000);
		mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
		game->plr.update = 0;
	}
	return (0);
}

int		key_hook(int keycode, t_game *game)
{
	const double	move_speed = 0.2;
	const double	rot_speed = 0.15;//0.321751;
	double			old_value;

	if (keycode == 65307)
		win_close(game);
	else if (keycode == 119) // up
	{
		game->plr.pos.x += game->plr.dir.x * move_speed;
		game->plr.pos.y += game->plr.dir.y * move_speed;
	}
	else if (keycode == 97) // left
	{
		game->plr.pos.x += game->plr.dir.y * move_speed;
		game->plr.pos.y -= game->plr.dir.x * move_speed;
	}
	else if (keycode == 115) // down
	{
		game->plr.pos.x -= game->plr.dir.x * move_speed;
		game->plr.pos.y -= game->plr.dir.y * move_speed;
	}
	else if (keycode == 100) // right
	{
		game->plr.pos.x -= game->plr.dir.y * move_speed;
		game->plr.pos.y += game->plr.dir.x * move_speed;
	}
	else if (keycode == 65361) // left rot
	{
		game->origin_angle -= acos(cos(rot_speed));
		old_value = game->plr.dir.x;
		game->plr.dir.x = game->plr.dir.x * cos(rot_speed) + game->plr.dir.y * sin(rot_speed);
		game->plr.dir.y = -old_value * sin(rot_speed) + game->plr.dir.y * cos(rot_speed);
	}
	else if (keycode == 65363) // right rot
	{
		game->origin_angle += acos(cos(rot_speed));
		old_value = game->plr.dir.x;
		game->plr.dir.x = game->plr.dir.x * cos(rot_speed) - game->plr.dir.y * sin(rot_speed);
		game->plr.dir.y = old_value * sin(rot_speed) + game->plr.dir.y * cos(rot_speed);
	}
	mlx_destroy_image(game->vars.mlx, game->img.img);
	game->plr.update = 1;
	return (0);
}

int	main()
{
	t_game	game;

	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, width, height, "Raycaster2D");

	game.plr.pos.x = 12;
	game.plr.pos.y = 12;
	game.plr.dir.x = 1;
	game.plr.dir.y = -1;
	game.plr.update = 1;
	game.origin_angle = -1.570796;

	printf("dx -> %lf\tdy -> %lf\n", sqrt(1 + pow(game.plr.dir.y / game.plr.dir.x, 2)), sqrt(1 + pow(game.plr.dir.x / game.plr.dir.y, 2)));
	
	mlx_hook(game.vars.win, 33, 0, &win_close, &game);
	mlx_hook(game.vars.win, 2, 1L<<0, &key_hook, &game);
	mlx_loop_hook(game.vars.mlx, &render_frame, &game);
	mlx_do_sync(game.vars.mlx);
	mlx_loop(game.vars.mlx);
}
