#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define	width	640
#define	height	480
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
  {1,0,0,2,2,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
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

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef	struct	s_plr
{
	t_point	pos;
	t_point	dir;
	t_vec	plane;
	double	dir_angel;
	int		start;
	int		end;
	int		color;
	int		update;
}				t_plr;

typedef	struct	s_game
{
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
	// return (keycode == 53 ? win_close(game) : 0);
	return (keycode == 65307 ? win_close(game) : 0);
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

int		isparallel(double a1, double a2, double b1, double b2)
{
	if (!(a1 * b2 - a2 * b1))
		return (1);
	return (0);
}

void	intersect(double p1[4], double p2[4], double *intersect)
{
	double k_line1[3];
	double k_line2[3];
	double det;

	k_line1[0] = p1[3] - p1[1];
	k_line1[1] = p1[0] - p1[2];
	k_line1[2] = -p1[0] * p1[3] + p1[1] * p1[2];
	k_line2[0] = p2[3] - p2[1];
	k_line2[1] = p2[0] - p2[2];
	k_line2[2] = -p2[0] * p2[3] + p2[1] * p2[2];
	det = k_line1[0] * k_line2[1] - k_line2[0] * k_line1[1];
	intersect[0] = (k_line1[1] * k_line2[2] - k_line2[1] * k_line1[2]) / det;
	intersect[1] = (k_line1[0] * k_line1[2] - k_line1[0] * k_line2[2]) / det;
}

void		raycaster(t_game *game)
{
	t_point			ray_pos;
	t_point			sray_pos;
	t_vec			tmp;
	const double	fov = 66 * M_PI / 180;
	double			ray_angle;
	double			dir_x;
	double			dir_y;
	double			dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
	
	for (int x = 0; x < width; x++)
	{
		double camera_plane = 2 * x / (double)width - 1;
		dir_x = game->plr.dir.x + game->plr.plane.x * camera_plane;
		dir_y = game->plr.dir.y + game->plr.plane.y * camera_plane;
		// printf("dir_x -> %lf\tdir_y -> %lf\n", dir_x, dir_y);
		ray_angle = game->plr.dir_angel - fov / 2 + fov * x / (double)width;
		// printf("%lf\n", ray_angle * 180 / M_PI);
		//printf("%lf\n", sin(ray_angle));
		sray_pos.x = game->plr.pos.x + dir_x;
		sray_pos.y = game->plr.pos.y + dir_y;
		for (double t = 0.0; t < 24; t += 0.5)
		{
			//ray_pos.x = game->plr.pos.x + dir_x + t * cos(game->plr.dir_angel);//game->plr.pos.x + t * cos(ray_angle);
			//ray_pos.y = game->plr.pos.y + dir_y + t * sin(game->plr.dir_angel);//game->plr.pos.x + t * sin(ray_angle);
			ray_pos.x = game->plr.pos.x + t * cos(ray_angle);
			ray_pos.y = game->plr.pos.y + t * sin(ray_angle);
			// printf("%d\n", worldMap[21][3]);
			if (worldMap[ray_pos.x][ray_pos.y] == 2)
				printf("ray_pos_x -> %d\tray_pos_y -> %d\n", ray_pos.x, ray_pos.y);
			if (worldMap[ray_pos.y][ray_pos.x] == 1 || worldMap[ray_pos.y][ray_pos.x] == 2)
			{
				// printf("%d\n", worldMap[ray_pos.x][ray_pos.y]);
				// printf("ray_x -> %d\tray_y -> %d\n", ray_pos.x, ray_pos.y);
				tmp.x = (ray_pos.x - sray_pos.x);
				tmp.y = (ray_pos.y - sray_pos.y);
				dist = sqrt(pow(tmp.x, 2) + pow(tmp.y, 2));//t * cos(ray_angle - game->plr.dir);//sqrt(pow(ray_pos.x - (game->plr.pos.x + tmp), 2) + pow(ray_pos.y - game->plr.pos.y, 2));
				// printf("%lf\n", dist);
				// dist *= cos(game->plr.dir_angel - ray_angle);
				// printf("%lf\n", cos(game->plr.dir_angel - ray_angle));
				// dist += sqrt(pow(ray_pos.x - game->plr.pos.x, 2) + pow(ray_pos.y - game->plr.pos.y, 2));
				// dist = sqrt(pow(dist * cos(ray_angle) * cos(ra), 2));
				// printf("%lf\n", game->plr.pos.x + dist * cos(ray_angle));
				// dist = dist * sin(ray_angle);
				line_height = (int)(height / dist);
				// printf("%d\n", line_height);
				// printf("%lf\n", dist);
				draw_start = -line_height / 2 + height / 2;
				if (draw_start < 0)
					draw_start = 0;
				draw_end = line_height / 2 + height / 2;
				if (draw_end >= height)
					draw_end = height - 1;
				if (worldMap[ray_pos.y][ray_pos.x] == 2)
				{
					// printf("%d\n", worldMap[ray_pos.y][ray_pos.x]);
					color = 0x00FF0000;
				}
				else
					color = 0x000000FF;
				// printf("start_draw -> %d\tend_draw -> %d\n", draw_start, draw_end);
				draw_vertline(x, draw_start, draw_end, game, color);
				// printf("%lf\n", cos(plr_dir));
				// printf("plr_x -> %d\tplr_y -> %d\n", plr_pos.x, plr_pos.y);
				
				// printf("dist -> %lf\n", dist);

				break ;
			}
		}
	}
	
	
	
	// double	camera_y;
	// double	ray_dir[2];
	// // double	map[2];
	// // double	pos[2];
	// int		x;

	// x = 0;
	// while (x < width)
	// {
	// 	camera_y = 2 * x / (double)width - 1;
	// 	ray_dir[0] = game->plr.dir[0] + game->plr.plane[0] * camera_y;
	// 	ray_dir[1] = game->plr.dir[1] + game->plr.plane[1] * camera_y;
		
	// 	// printf("ray_x -> %f\tray_y -> %f\n", ray_dir[0], ray_dir[1]);
	// 	x++;
	// }
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

int			choice_key(int keycode, t_game *game)
{
	// printf("keycode -> %d\n", keycode);
	win_close_esc(keycode, game);
	// shift(keycode, game);
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
	

	game.plr.pos.x = 8;
	game.plr.pos.y = 18;
	game.plr.dir_angel = M_PI / 2;
	game.plr.dir.x = 0;
	game.plr.dir.y = 1;
	game.plr.plane.x = 0.66;
	game.plr.plane.y = 0.0;

	// game.plr.pos[0] = 4;
	// game.plr.pos[1] = 2;
	// game.plr.dir[0] = 0;
	// game.plr.dir[1] = 1;
	// game.plr.plane[0] = 0.66;
	// game.plr.plane[1] = 0;
	// game.plr.plane[0] = game.plr.plane[0] * cos(3.14);
	// game.plr.plane[1] = game.plr.plane[1] * cos(3.14);
	// printf("planeX -> %f\nplaneY -> %f\n", game.plr.plane[0], game.plr.plane[1]);
	game.plr.update = 1;

	raycaster(&game);

	// mlx_hook(game.vars.win, 17, 0, &win_close, &game);
	mlx_hook(game.vars.win, 33, 0, &win_close, &game);
	mlx_hook(game.vars.win, 2, 1L<<0, &choice_key, &game);
	mlx_loop_hook(game.vars.mlx, &render_frame, &game);
	mlx_do_sync(game.vars.mlx);
	mlx_loop(game.vars.mlx);
}
