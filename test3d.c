#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define	width	1280
#define	height	960
#define mapWidth 24
#define mapHeight 24

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
  {1,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

typedef	struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef	struct	s_plr
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	int		start;
	int		end;
	int		color;
	int		update;
}				t_plr;

typedef	struct	s_game
{
	int		x;
	int		y;
	t_data	img;
	t_vars	vars;
	t_plr	plr;
}				t_game;

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
	return (keycode == 65307/*53*/ ? win_close(game) : 0);
}

void		draw_vertline(int x, int start, int end, t_game *game, int color)
{
	int i;
	// int color = 0x750000FF;

	i = start;
	while (i < end)
	{
		my_mlx_pixel_put(&game->img, x, i, color);
		i++;
	}
	// mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
}

int			raycaster(t_game *game)
{
	int 	x;
	double	camera_x;
	double	ray_dir[2];
	int		map[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	perp_wall_dist;
	int		step[2];
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	color = 0x000000FF;
	x = 0;
	while (x < width)
	{
		camera_x = 2 * x / (double)width - 1;
		ray_dir[0] = game->plr.dir[0] + game->plr.plane[0] * camera_x;
		ray_dir[1] = game->plr.dir[1] + game->plr.plane[1] * camera_x;

		map[0] = (int)game->plr.pos[0];
		map[1] = (int)game->plr.pos[1];

		delta_dist[0] = fabs(1 / ray_dir[0]);
		delta_dist[1] = fabs(1 / ray_dir[1]);

		hit = 0;
		if (ray_dir[0] < 0)
		{
			step[0] = -1;
			side_dist[0] = (game->plr.pos[0] - map[0]) * delta_dist[0];
		}
		else
		{
			step[0] = 1;
			side_dist[0] = (map[0] + 1.0 - game->plr.pos[0]) * delta_dist[0];
		}
		if (ray_dir[1] < 0)
		{
			step[1] = -1;
			side_dist[1] = (game->plr.pos[1] - map[1]) * delta_dist[1];
		}
		else
		{
			step[1] = 1;
			side_dist[1] = (map[1] + 1.0 - game->plr.pos[1]) * delta_dist[1];
		}
		while (!hit)
		{
			if (side_dist[0] < side_dist[1])
			{
				side_dist[0] += delta_dist[0];
				map[0] += step[0];
				side = 0;
			}
			else
			{
				side_dist[1] += delta_dist[1];
				map[1] += step[1];
				side = 1;
			}
			if (worldMap[map[0]][map[1]] > 0)
				hit = 1;
		}
		if (!side)
			perp_wall_dist = (map[0] - game->plr.pos[0] + (1 - step[0]) / 2) / ray_dir[0];
		else
			perp_wall_dist = (map[1] - game->plr.pos[1] + (1 - step[1]) / 2) / ray_dir[1];
		// printf("%f\n", perp_wall_dist);
		line_height = (int)(height / perp_wall_dist);

		draw_start = -line_height / 2 + height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + height / 2;
		if (draw_end >= height)
			draw_end = height - 1;
		if (worldMap[map[0]][map[1]] == 2)
			color = 0x00FF0000;
		else
			color = 0x000000FF;
		if (side == 1)
			color = color / 2;
		game->plr.start = draw_start;
		game->plr.end = draw_end;
		game->plr.color = color;
		draw_vertline(x, draw_start, draw_end, game, color);
		x++;
	}
	return (0);
}

void		clc_img(t_game *game)
{
	int i;

	i = 0;
	while (i < width)
	{
		draw_vertline(i, 0, height, game, 0x00000000);
		// draw_vertline(i, game->plr.start, game->plr.end, game, 0x00000000);
		i++;
	}
}

// double	get_a(double y1, double y2)
// {

// }

// void	get_b()
// {

// }

void		shift(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double 	buf;

	move_speed = 0.1;
	rot_speed = 0.05;

	// clc_img(game);
	// printf("key -> %d\n", keycode);
	if (keycode == 119)//13) // up
	{
		if (!worldMap[(int)(game->plr.pos[0] + game->plr.dir[0] * move_speed)][(int)(game->plr.pos[1])])
			game->plr.pos[0] += game->plr.dir[0] * move_speed;
		if (!worldMap[(int)(game->plr.pos[0])][(int)(game->plr.pos[1] + game->plr.dir[1] * move_speed)])
			game->plr.pos[1] += game->plr.dir[1] * move_speed;
	}
	else if (keycode == 97)//0) // left
	{
		buf = game->plr.dir[1] * sin(1.57) * move_speed;
		if (!worldMap[(int)(game->plr.pos[0] + buf)][(int)(game->plr.pos[1])])
			game->plr.pos[0] += buf;
		buf = game->plr.dir[0] * sin(1.57) * move_speed;
		if (!worldMap[(int)(game->plr.pos[0])][(int)(game->plr.pos[1] - buf)])
			game->plr.pos[1] -= buf;
	}
	else if (keycode == 115)//1) // down
	{
		if (!worldMap[(int)(game->plr.pos[0] - game->plr.dir[0] * move_speed)][(int)game->plr.pos[1]])
			game->plr.pos[0] -= game->plr.dir[0] * move_speed;	
		if (!worldMap[(int)game->plr.pos[0]][(int)(game->plr.pos[1] - game->plr.dir[1] * move_speed)])
			game->plr.pos[1] -= game->plr.dir[1] * move_speed;
	}
	else if (keycode == 100)//2) // right
	{
		buf = game->plr.dir[1] * sin(1.57) * move_speed;
		if (!worldMap[(int)(game->plr.pos[0] - buf)][(int)(game->plr.pos[1])])
			game->plr.pos[0] -= buf;
		buf = game->plr.dir[0] * sin(1.57) * move_speed;
		if (!worldMap[(int)(game->plr.pos[0])][(int)(game->plr.pos[1] + buf)])
			game->plr.pos[1] += buf;
	}
	else if (keycode == 65361)//123) // right rot
	{
		double olddir_x = game->plr.dir[0];
		game->plr.dir[0] = game->plr.dir[0] * cos(rot_speed) - game->plr.dir[1] * sin(rot_speed);
		game->plr.dir[1] = olddir_x * sin(rot_speed) + game->plr.dir[1] * cos(rot_speed);
		double oldplane_x = game->plr.plane[0];
		game->plr.plane[0] = game->plr.plane[0] * cos(rot_speed) - game->plr.plane[1] * sin(rot_speed);
		game->plr.plane[1] = oldplane_x * sin(rot_speed) + game->plr.plane[1] * cos(rot_speed);
	}
	else if (keycode == 65363)//124) // left rot
	{
		double olddir_x = game->plr.dir[0];
		game->plr.dir[0] = game->plr.dir[0] * cos(-rot_speed) - game->plr.dir[1] * sin(-rot_speed);
		game->plr.dir[1] = olddir_x * sin(-rot_speed) + game->plr.dir[1] * cos(-rot_speed);
		double oldplane_x = game->plr.plane[0];
		game->plr.plane[0] = game->plr.plane[0] * cos(-rot_speed) - game->plr.plane[1] * sin(-rot_speed);
		game->plr.plane[1] = oldplane_x * sin(-rot_speed) + game->plr.plane[1] * cos(-rot_speed);
	}
	game->plr.update = 1;
	// clc_img(game);
	// raycaster(game);
	// clc_img(game);

	// raycaster(game);
	// mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	// clc_img(game);
}

int			choice_key(int keycode, t_game *game)
{
	// printf("keycode -> %d\n", keycode);
	win_close_esc(keycode, game);
	shift(keycode, game);
	// shift_item(keycode, game);
	return (0);
}

int			render_frame(t_game *game)
{
	// clc_img(game);
	// raycaster(game);
	if (game->plr.update)
	{
		clc_img(game);
		raycaster(game);
		game->plr.update = 0;
	}
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	// clc_img(game);
	return (0);
}

int			main()
{
	t_game	game;

	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, width, height, "Game");
	game.img.img = mlx_new_image(game.vars.mlx, width, height);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
                                 &game.img.endian);
	
	game.plr.pos[0] = 15;
	game.plr.pos[1] = 5;
	game.plr.dir[0] = 1;
	game.plr.dir[1] = 0;
	game.plr.plane[0] = 0;
	game.plr.plane[1] = 0.66;
	game.plr.plane[0] = game.plr.plane[0] * cos(3.14);
	game.plr.plane[1] = game.plr.plane[1] * cos(3.14);
	// printf("planeX -> %f\nplaneY -> %f\n", game.plr.plane[0], game.plr.plane[1]);
	game.plr.update = 1;

	// raycaster(&game);

	mlx_hook(game.vars.win, 33, 0, &win_close, &game);
	mlx_hook(game.vars.win, 2, 1L<<0, &choice_key, &game);
	mlx_loop_hook(game.vars.mlx, &render_frame, &game);
	mlx_do_sync(game.vars.mlx);
	mlx_loop(game.vars.mlx);
}
