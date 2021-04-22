#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

#define	width	1280
#define	height	1024
#define mapWidth 24
#define mapHeight 24

#define	PSQUARE 30
#define OFFSET	200

#define ESC_U 65307
#define W_U 'w'
#define A_U 'a'
#define S_U 's'
#define D_U 'd'
#define L_ARROW_U 65361
#define R_ARROW_U 65363

#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2
#define L_ARROW 123
#define R_ARROW 124

#define W_PRESS			0b00000001
#define A_PRESS			0b00000010
#define S_PRESS			0b00000100
#define D_PRESS			0b00001000
#define L_ARROW_PRESS	0b00010000
#define R_ARROW_PRESS	0b00100000
#define RESET			0b00000000

unsigned int flags = 0;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1},
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
	t_point	plane;
	double	origin_angle;
}				t_game;

int		win_close(t_game *game)
{
	// mlx_destroy_image(game->vars.mlx, game->img.img);
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

void	draw_vec(t_game *game, double x1, double y1, double x2, double y2, int color)
{
	int x;
	int y;
	int e_x;
	int e_y;
	int s_x;
	int s_y;
	double k;

	s_x = OFFSET + x1 * PSQUARE;
	s_y = OFFSET + y1 * PSQUARE;;
	e_x = OFFSET + (x1 + (x2 - x1)) * PSQUARE;
	e_y = OFFSET + (y1 + (y2 - y1)) * PSQUARE;
	x = s_x;
	y = s_y;
	k = 0.01;
	while (k <= 200)
	{
		x = (s_x + k * e_x) / (1 + k);
		y = (s_y + k * e_y) / (1 + k);
		pixel_put(&game->img, x, y, color);
		// printf("x -> %d\ty -> %d\n", x, y);
		k += 0.01;
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
				draw_rectangle(game, draw_x - PSQUARE / 2, draw_y - PSQUARE / 2, 0x00FFFFFF, PSQUARE);
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
	// printf("x -> %lf\ty -> %lf\n", game->plr.pos.x, game->plr.pos.y);
	draw_rectangle(game, x - 5, y - 5, 0x0000FF00, 10);
}

void	draw_line(t_game *game, int line, int draw_start, int draw_end, int color)
{
	while (draw_start < draw_end)
	{
		pixel_put(&game->img, line, draw_start, color);
		draw_start++;
	}
}

void	draw_grid(t_game *game)
{
	int x;
	int y;

	x = OFFSET + PSQUARE;
	while (x < OFFSET + mapWidth * PSQUARE)
	{
		y = OFFSET;
		while (y < OFFSET + mapHeight * PSQUARE)
		{
			pixel_put(&game->img, x - PSQUARE / 2, y - PSQUARE / 2, 0x000000FF);
			y += 1;
		}
		x += PSQUARE;
	}
	y = OFFSET + PSQUARE;
	while (y < OFFSET + mapHeight * PSQUARE)
	{
		x = OFFSET;
		while (x < OFFSET + mapWidth * PSQUARE)
		{
			pixel_put(&game->img, x - PSQUARE / 2, y - PSQUARE / 2, 0x000000FF);
			x++;
		}
		y += PSQUARE;
	}
}

void	raycaster(t_game *game)
{
	double		ray_x;
	double		ray_y;
	double	kx;
	double	ky;
	double	side_x;
	double	side_y;
	int		ray_map_posx;
	int		ray_map_posy;
	int		ishit;
	int		step_x;
	int		step_y;
	t_point	intersect;
	int		side_map;
	double		x;

	x = -1.0;
	while (x < 1.0)
	{
		ray_x = game->plr.dir.x + game->plane.x * x;
		ray_y = game->plr.dir.y + game->plane.y * x;
		ray_map_posx = game->plr.pos.x;
		ray_map_posy = game->plr.pos.y;
		kx = fabs(1 / ray_x); /*sqrt(1 + pow(1 / game->plr.dir.x, 2));*/ //game->plr.dir.y == 0 ? 0 : (game->plr.dir.x == 0 ? 1 : sqrt(1 + pow(1 / game->plr.dir.x, 2)));
		ky = fabs(1 / ray_y); /*sqrt(1 + pow(1 / game->plr.dir.y, 2));*/ //game->plr.dir.x == 0 ? 0 : (game->plr.dir.y == 0 ? 1 : sqrt(1 + pow(1 / game->plr.dir.y, 2)));
		// printf("kx -> %lf\tky -> %lf\n", kx, ky);
		// printf("ray_x -> %lf\tray_y -> %lf\n", ray_x, ray_y);
		// printf("ray_len -> %lf\n", sqrt(pow(ray_x, 2) + pow(ray_y, 2)));
		if (ray_x > 0)
		{
			side_x = (ray_map_posx + 1.0 - game->plr.pos.x) * kx;
			step_x = 1;
		}
		else
		{
			side_x = (game->plr.pos.x - ray_map_posx) * kx;
			step_x = -1;
		}
		if (ray_y > 0)
		{
			side_y = (ray_map_posy + 1.0 - game->plr.pos.y) * ky;
			step_y = 1;
		}
		else
		{
			side_y = (game->plr.pos.y - ray_map_posy) * ky;
			step_y = -1;
		}
		// printf("side_x -> %lf\tside_y -> %lf\n", side_x, side_y);
		ishit = 0;
		while (!ishit)
		{
			if (side_x < side_y)
			{
				// printf("TUT\n");
				side_x += kx;
				ray_map_posx += step_x;
				side_map = 1;
			}
			else
			{
				// printf("TUT2\n");
				side_y += ky;
				ray_map_posy += step_y;
				side_map = 0;
			}
			// printf("x -> %d\ty -> %d\n", ray_map_posy, ray_map_posx);
			if (worldMap[ray_map_posy][ray_map_posx])
				ishit = 1;
			// if (ray_map_posx < width || ray_map_posy < height)
			// 	break ;
			if (ray_map_posx > width || ray_map_posy > height)
				break ;
		}
		intersect.x = ray_map_posx;
		if (side_map && game->plr.dir.x > 0)
			intersect.x = ray_map_posx - 0.5;//(game->plr.pos.x + 20 * ray_map_posx) / 21;
		else if (side_map && game->plr.dir.x < 0)
			intersect.x = ray_map_posx + 0.5;
		intersect.y = ray_map_posy;
		if (!side_map && game->plr.dir.y > 0)
			intersect.y = ray_map_posy - 0.5;//(game->plr.pos.y + 20 * ray_map_posy) / 21;
		else if (!side_map && game->plr.dir.y < 0)
			intersect.y = ray_map_posy + 0.5;
		draw_vec(game, game->plr.pos.x, game->plr.pos.y, intersect.x, intersect.y, 0x00FF0000);
		// draw_vec(game, game->plr.pos.x, game->plr.pos.y, ray_map_posx, ray_map_posy, 0x00FF0000);
		x += 0.05;
	}
}

int		render_frame(t_game *game)
{
	ft_bzero(game->img.addr, (height - 0) * game->img.line_length +
		(width - 1) * (game->img.bits_per_pixel / 8));
	// draw fun
	// game->img.img = mlx_new_image(game->vars.mlx, width, height);
	// game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
	// 	&game->img.endian);
	// game->img.img = mlx_new_image(game->vars.mlx, width, height);
	// game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
	// 	&game->img.endian);
	draw_map(game);
	draw_grid(game);
	draw_plr(game);
	if ((int)(game->plr.pos.x) < mapWidth && (int)(game->plr.pos.x) > 0
		&& (int)(game->plr.pos.y) < mapHeight && (int)(game->plr.pos.y) > 0)
		raycaster(game);
	draw_dir(game, 0x0000FF00);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	mlx_do_sync(game->vars.mlx);
	// mlx_destroy_image(game->vars.mlx, game->img.img);
	return (0);
}

int		key_hook(int keycode, t_game *game)
{
	const double	move_speed = 0.3;
	const double	rot_speed = 0.2;//0.321751;
	double			old_value;

	if (keycode == 65307 || keycode == 53)
		win_close(game);
	else if (keycode == 119 || keycode == 13) // up
	{
		game->plr.pos.x += game->plr.dir.x * move_speed;
		game->plr.pos.y += game->plr.dir.y * move_speed;
	}
	else if (keycode == 97 || keycode == 0) // left
	{
		game->plr.pos.x -= game->plane.x * move_speed;
		game->plr.pos.y -= game->plane.y * move_speed;
	}
	else if (keycode == 115 || keycode == 1) // down
	{
		game->plr.pos.x -= game->plr.dir.x * move_speed;
		game->plr.pos.y -= game->plr.dir.y * move_speed;
	}
	else if (keycode == 100 || keycode == 2) // right
	{
		game->plr.pos.x += game->plane.x * move_speed;
		game->plr.pos.y += game->plane.y * move_speed;
	}
	else if (keycode == 65361 || keycode == 123) // left rot
	{
		game->origin_angle -= acos(cos(rot_speed));
		old_value = game->plr.dir.x;
		game->plr.dir.x = game->plr.dir.x * cos(rot_speed) + game->plr.dir.y * sin(rot_speed);
		game->plr.dir.y = -old_value * sin(rot_speed) + game->plr.dir.y * cos(rot_speed);
		old_value = game->plane.x;
		game->plane.x = game->plane.x * cos(rot_speed) + game->plane.y * sin(rot_speed);
		game->plane.y = -old_value * sin(rot_speed) + game->plane.y * cos(rot_speed);
	}
	else if (keycode == 65363 || keycode == 124) // right rot
	{
		game->origin_angle += acos(cos(rot_speed));
		old_value = game->plr.dir.x;
		game->plr.dir.x = game->plr.dir.x * cos(rot_speed) - game->plr.dir.y * sin(rot_speed);
		game->plr.dir.y = old_value * sin(rot_speed) + game->plr.dir.y * cos(rot_speed);
		old_value = game->plane.x;
		game->plane.x = game->plane.x * cos(rot_speed) - game->plane.y * sin(rot_speed);
		game->plane.y = old_value * sin(rot_speed) + game->plane.y * cos(rot_speed);
	}
	// printf("or_angle -> %lf\n", game->origin_angle);
	return (0);
}

int	main()
{
	t_game	game;

	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, width, height, "Raycaster2D");
	game.img.img = mlx_new_image(game.vars.mlx, width, height);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
		&game.img.endian);

	game.plr.pos.x = 12;
	game.plr.pos.y = 12;
	game.plr.dir.x = 0;
	game.plr.dir.y = -1;
	game.plane.x = 0.66;
	game.plane.y = 0;
	game.plr.update = 1;
	game.origin_angle = 1.570796;

	// printf("dx -> %lf\tdy -> %lf\n", sqrt(1 + pow(game.plr.dir.y / game.plr.dir.x, 2)), sqrt(1 + pow(game.plr.dir.x / game.plr.dir.y, 2)));
	
	mlx_hook(game.vars.win, 17, 0, &win_close, &game);
	mlx_hook(game.vars.win, 2, 1L<<0, &key_hook, &game);
	mlx_loop_hook(game.vars.mlx, &render_frame, &game);
	mlx_loop(game.vars.mlx);
}
