#include "mlx.h"
#include "libft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define	width	1920//640
#define	height	1080//480
#define mapWidth 6
#define mapHeight 4
#define spritesCount 1

double zbuf[width];
int		sprite_order[spritesCount];
double	sprites_dist[spritesCount];

// int worldMap[mapWidth][mapHeight]=
// { 	
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1},
//   {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

int	worldMap[mapWidth][mapHeight] =
{
	{1, 1, 1, 1},
	{1, 0, 0, 1},
	{1, 0, 0, 1},
	{1, 0, 0, 1},
	{1, 0, 0, 1},
	{1, 1, 1, 1}
};

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct	s_texture
{
	t_data img;
	int w;
	int h;
}				t_texture;

typedef struct	s_sprite
{
	int			x;
	int			y;
	t_texture	img;
}				t_sprite;

t_sprite sprite[spritesCount];

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
}				t_plr;

typedef	struct	s_game
{
	t_data		img;
	t_texture	tex;
	t_texture	tex2;
	t_vars		vars;
	t_plr		plr;
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
	mlx_destroy_image(game->vars.mlx, game->tex.img.img);
	mlx_destroy_image(game->vars.mlx, game->tex2.img.img);
	mlx_destroy_image(game->vars.mlx, game->img.img);
	win_close(game);
	//return (keycode == 53 ? win_close(game) : 0);
	// return (keycode == 65307 ? win_close(game) : 0);
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

void		draw_sky(int x, int end, t_game *game, int color)
{
	int i;

	i = 0;
	while (i < end)
	{
		my_mlx_pixel_put(&game->img, x, i, color);
		i++;
	}
}

void		draw_floor(int x, int start, int end, t_game *game, int color)
{
	int i;

	i = start;
	while (i < end)
	{
		my_mlx_pixel_put(&game->img, x, i, color);
		i++;
	}
}

void		ft_sort(int *sprite_order, double *sprites_dist, int count)
{
	int i;
	int j;
	int isswap;
	int tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		isswap = 0;
		while (j < count - i - 1)
		{
			if (sprites_dist[j] < sprites_dist[j + 1])
			{
				tmp = sprites_dist[j];
				sprites_dist[j] = sprites_dist[j + 1];
				sprites_dist[j + 1] = tmp;
				tmp = sprite_order[j];
				sprite_order[j] = sprite_order[j + 1];
				sprite_order[j + 1] = tmp;
				isswap = 1;
			}
			j++;
		}
		if (!isswap)
			break ;
		i++;
	}
}

int			get_color(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
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
	// game->plr.pos[0] += 1;
	// game->plr.pos[1] += 1;
	while (x < width)
	{
		camera_x = 2 * x / (double)width - 1;
		ray_dir[0] = game->plr.dir[0] + game->plr.plane[0] * camera_x;
		ray_dir[1] = game->plr.dir[1] + game->plr.plane[1] * camera_x;

		// printf("dir_x -> %lf\tdir_y -> %lf\n", ray_dir[0], ray_dir[1]);

		map[0] = (int)game->plr.pos[0];
		map[1] = (int)game->plr.pos[1];

		delta_dist[0] = fabs(1 / ray_dir[0]);
		delta_dist[1] = fabs(1 / ray_dir[1]);
		// printf("side_x -> %lf\tside_y -> %lf\n", delta_dist[0], delta_dist[1]);
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
		// printf("side_x -> %lf\tside_y -> %lf\n", side_dist[0], side_dist[1]);
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
			if (worldMap[map[0]][map[1]] == 1)
				hit = 1;
		}
		if (!side)
			perp_wall_dist = (map[0] - game->plr.pos[0] + (1 - step[0]) / 2) / ray_dir[0];
		else
			perp_wall_dist = (map[1] - game->plr.pos[1] + (1 - step[1]) / 2) / ray_dir[1];
		// printf("%f\n", perp_wall_dist);
		line_height = (int)(height / perp_wall_dist);
		if (line_height < 30) printf("%d\n", line_height);

		draw_start = -line_height / 2 + height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + height / 2;
		if (draw_end >= height)
			draw_end = height - 1;
		double wallx;
		if (side == 0)	wallx = game->plr.pos[1] + perp_wall_dist * ray_dir[1];
		else			wallx = game->plr.pos[0] + perp_wall_dist * ray_dir[0];
		// printf("wallx -> %lf\tfloor(wallx) -> %lf\n", wallx, wallx - floor(wallx));
		wallx -= floor(wallx);
		int h;
		int w;
		if (side)
		{
			h = game->tex.h; // texture height
			w = game->tex.w; // texture width
		}
		else
		{
			h = game->tex2.h; // texture height
			w = game->tex2.w; // texture width
		}

		int tex_x = (int)(wallx * (double)(w));
		// if (side == 0 && ray_dir[0] > 0) tex_x = w - tex_x - 1;
		// if (side == 1 && ray_dir[1] < 0) tex_x = w - tex_x - 1;
		double step_tex = (double)h / line_height;
		double texPos = (draw_start - height / 2 + line_height / 2) * step_tex;
		for (int y = draw_start; y < draw_end; y++)
		{
			//(int)texPos & (h - 1);
			int tex_y = texPos;
			texPos += step_tex;
			// printf("tex_x -> %d\ttex_y -> %d\n", tex_x, tex_y);
			// data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
			if (!side)
				color = *(unsigned int*)(game->tex.img.addr + (tex_y * game->tex.img.line_length + (game->tex.img.bits_per_pixel / 8) * tex_x));
			else
				color = *(unsigned int*)(game->tex2.img.addr + (tex_y * game->tex2.img.line_length + (game->tex2.img.bits_per_pixel / 8) * tex_x));
			// printf("%d\n", tex_y * game->tex.img.line_length + (game->tex.img.bits_per_pixel / 8) * tex_x);
			// color = *(unsigned int*)(game->tex.img.addr + (tex_x * texHeight + tex_y));
			// if (side)
			// 	color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&game->img, x, y, color);
		}
		draw_floor(x, draw_end, height - 1, game, get_color(0, 220, 100, 0));//0xd4d7ea);
		draw_sky(x, draw_start, game, 0x8aadfb);
		// draw_vertline(x, draw_start, draw_end, game, color);
		zbuf[x] = perp_wall_dist;
		x++;
	}

	int i = 0;
	sprite[0].x = 2;
	sprite[0].y = 2;
	// sprite[1].x = 4;
	// sprite[1].y = 2;
	// sprite[2].x = 2;
	// sprite[2].y = 4;
	while (i < spritesCount)
	{
		sprite_order[i] = i;
		sprites_dist[i] = pow(game->plr.pos[0] - sprite[i].x, 2) + pow(game->plr.pos[1] - sprite[i].y, 2);
		i++;
	}
	// можно сортировать сразу массив спрайтов (но не точно)
	ft_sort(sprite_order, sprites_dist, spritesCount);
	i = 0;
	while (i < spritesCount)
	{
		double sprite_x = sprite[sprite_order[i]].x - game->plr.pos[0];
		double sprite_y = sprite[sprite_order[i]].y - game->plr.pos[1];

		double inv_det = 1.0 / (game->plr.plane[0] * game->plr.dir[1] - game->plr.plane[1] * game->plr.dir[0]);

		double tr_x = inv_det * (game->plr.dir[1] * sprite_x - game->plr.dir[0] * sprite_y);
		double tr_y = inv_det * (-game->plr.plane[1] * sprite_x + game->plr.plane[0] * sprite_y);

		int sprite_scr_x = (int)((width / 2) * (1 + tr_x / tr_y));

		// убрать нахер
		#define uDiv 1
      	#define vDiv 1
      	#define vMove 0.0
		// -------------
		int v_move_scr = (int)(vMove / tr_y);
		int sprite_h = abs((int)(height / tr_y)) / vDiv;
		int draw_start_y = -sprite_h / 2 + height / 2 + v_move_scr;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_h / 2 + height / 2 + v_move_scr;
		if (draw_end_y >= height)
			draw_end_y = height - 1;

		int sprite_w = abs((int)(height / tr_y)) / uDiv;
		int draw_start_x = -sprite_w / 2 + sprite_scr_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_w / 2 + sprite_scr_x;
		if (draw_end_x >= width)
			draw_end_x = width - 1;
		
		int stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_w / 2 + sprite_scr_x)) * sprite[sprite_order[i]].img.w / sprite_w) / 256;
			if (tr_y > 0 && stripe > 0 && stripe < width && tr_y < zbuf[stripe])
			{
				int y_y = draw_start_y;
				while (y_y < draw_end_y)
				{
					int d = (y_y - v_move_scr) * 256 - height * 128 + sprite_h * 128;
					int tex_y = ((d * sprite[sprite_order[i]].img.h) / sprite_h) / 256;
					color = *(unsigned int*)(sprite[sprite_order[i]].img.img.addr + (tex_y * sprite[sprite_order[i]].img.img.line_length + (sprite[sprite_order[i]].img.img.bits_per_pixel / 8) * tex_x));
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&game->img, stripe, y_y, color);
					y_y++;
				}
			}
			stripe++;
		}
		i++;
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

void		shift(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double 	buf;

	move_speed = 0.1;
	rot_speed = 0.15;

	// clc_img(game);
	// printf("key -> %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
		win_close_esc(keycode, game);
	else if (keycode == 119 || keycode == 13) // up 13
	{
		if (worldMap[(int)(game->plr.pos[0] + game->plr.dir[0] * move_speed)][(int)(game->plr.pos[1])] != 1)
			game->plr.pos[0] += game->plr.dir[0] * move_speed;
		if (worldMap[(int)(game->plr.pos[0])][(int)(game->plr.pos[1] + game->plr.dir[1] * move_speed)] != 1)
			game->plr.pos[1] += game->plr.dir[1] * move_speed;
	}
	else if (keycode == 97 || keycode == 2) // left 2
	{
		// buf = game->plr.dir[1] * sin(1.57) * move_speed;
		buf = game->plr.dir[1] * move_speed;
		if (worldMap[(int)(game->plr.pos[0] - buf)][(int)(game->plr.pos[1])] != 1)
			game->plr.pos[0] -= game->plr.plane[0] * move_speed;
		// buf = game->plr.dir[0] * sin(1.57) * move_speed;
		buf = game->plr.dir[0] * move_speed;
		if (worldMap[(int)(game->plr.pos[0])][(int)(game->plr.pos[1] + buf)] != 1)
			game->plr.pos[1] -= game->plr.plane[1] * move_speed;
	}
	else if (keycode == 115 || keycode == 1) // down 1
	{
		if (worldMap[(int)(game->plr.pos[0] - game->plr.dir[0] * move_speed)][(int)game->plr.pos[1]] != 1)
			game->plr.pos[0] -= game->plr.dir[0] * move_speed;	
		if (worldMap[(int)game->plr.pos[0]][(int)(game->plr.pos[1] - game->plr.dir[1] * move_speed)] != 1)
			game->plr.pos[1] -= game->plr.dir[1] * move_speed;
	}
	else if (keycode == 100 || keycode == 0) // right
	{
		// buf = game->plr.dir[1] * sin(1.57) * move_speed;
		buf = game->plr.dir[1] * move_speed;
		if (worldMap[(int)(game->plr.pos[0] + buf)][(int)(game->plr.pos[1])] != 1)
			game->plr.pos[0] += game->plr.plane[0] * move_speed;
		// buf = game->plr.dir[0] * sin(1.57) * move_speed;
		buf = game->plr.dir[0] * move_speed;
		if (worldMap[(int)(game->plr.pos[0])][(int)(game->plr.pos[1] - buf)] != 1)
			game->plr.pos[1] += game->plr.plane[1] * move_speed;
	}
	else if (keycode == 65361 || keycode == 123) // left rot
	{
		double olddir_x = game->plr.dir[0];
		game->plr.dir[0] = game->plr.dir[0] * cos(rot_speed) - game->plr.dir[1] * sin(rot_speed);
		game->plr.dir[1] = olddir_x * sin(rot_speed) + game->plr.dir[1] * cos(rot_speed);
		double oldplane_x = game->plr.plane[0];
		game->plr.plane[0] = game->plr.plane[0] * cos(rot_speed) - game->plr.plane[1] * sin(rot_speed);
		game->plr.plane[1] = oldplane_x * sin(rot_speed) + game->plr.plane[1] * cos(rot_speed);
	}
	else if (keycode == 65363 || keycode == 124) // right rot
	{
		double olddir_x = game->plr.dir[0];
		game->plr.dir[0] = game->plr.dir[0] * cos(-rot_speed) - game->plr.dir[1] * sin(-rot_speed);
		game->plr.dir[1] = olddir_x * sin(-rot_speed) + game->plr.dir[1] * cos(-rot_speed);
		double oldplane_x = game->plr.plane[0];
		game->plr.plane[0] = game->plr.plane[0] * cos(-rot_speed) - game->plr.plane[1] * sin(-rot_speed);
		game->plr.plane[1] = oldplane_x * sin(-rot_speed) + game->plr.plane[1] * cos(-rot_speed);
	}
	// game->plr.update = 1;
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
	// win_close_esc(keycode, game);
	shift(keycode, game);
	// shift_item(keycode, game);
	return (0);
}

int			render_frame(t_game *game)
{
	size_t n;
	// game->img.img = mlx_new_image(game->vars.mlx, width, height);
	// game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
    //                              &game->img.endian);
		// printf("line_len -> %d\n", game->img.line_length / width);
		// printf("bits_per_pixel -> %d\n", game->img.bits_per_pixel);
		// printf("endian -> %d\n", game->img.endian);
		// clc_img(game);
	n = height * game->img.line_length + width * (game->img.bits_per_pixel / 8);
	ft_bzero(game->img.addr, n);
	raycaster(game);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	mlx_do_sync(game->vars.mlx);
	// mlx_destroy_image(game->vars.mlx, game->img.img);
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
	game.plr.pos[0] = 2;
	game.plr.pos[1] = 2;
	game.plr.dir[0] = -1;
	game.plr.dir[1] = 0;
	game.plr.plane[0] = 0;
	game.plr.plane[1] = 0.66;
	game.plr.plane[0] = game.plr.plane[0];
	game.plr.plane[1] = game.plr.plane[1];
	printf("planeX -> %f\nplaneY -> %f\t%f\n", game.plr.plane[0], game.plr.plane[1], cos(-3.14));


	game.tex.img.img = mlx_xpm_file_to_image(game.vars.mlx, "textures/redbrick_1.xpm", &game.tex.w, &game.tex.h);
	if (game.tex.img.img == NULL)
		exit(1);
	game.tex.img.addr = mlx_get_data_addr(game.tex.img.img, &game.tex.img.bits_per_pixel, &game.tex.img.line_length,
		&game.tex.img.endian);

	game.tex2.img.img = mlx_xpm_file_to_image(game.vars.mlx, "textures/mossy.xpm", &game.tex2.w, &game.tex2.h);
	if (game.tex2.img.img == NULL)
		exit(1);
	game.tex2.img.addr = mlx_get_data_addr(game.tex2.img.img, &game.tex2.img.bits_per_pixel, &game.tex2.img.line_length,
		&game.tex2.img.endian);

	sprite[0].img.img.img = mlx_xpm_file_to_image(game.vars.mlx, "textures/barrel.xpm", &sprite[0].img.w, &sprite[0].img.h);
	if (sprite[0].img.img.img == NULL)
		exit(1);
	sprite[0].img.img.addr = mlx_get_data_addr(sprite[0].img.img.img, &sprite[0].img.img.bits_per_pixel, &sprite[0].img.img.line_length, &sprite[0].img.img.endian);
	// raycaster(&game);

	mlx_hook(game.vars.win, 33, 0, &win_close, &game);
	mlx_hook(game.vars.win, 2, 1L<<0, &choice_key, &game);
	mlx_loop_hook(game.vars.mlx, &render_frame, &game);
	mlx_loop(game.vars.mlx);
}
