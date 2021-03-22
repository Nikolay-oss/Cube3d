/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 04:52:24 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/18 14:23:39 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include <stdlib.h>
# include "mlx.h"
# include "ft_parser.h"

# define ESC_U 65307
# define W_U 119
# define A_U 97
# define S_U 115
# define D_U 100
# define L_ARROW_U 65361
# define R_ARROW_U 65363

# define ESC 53
# define W 13
# define A 2
# define S 1
# define D 0
# define L_ARROW 123
# define R_ARROW 124

# define W_PRESS		0b00000001
# define A_PRESS		0b00000010
# define S_PRESS		0b00000100
# define D_PRESS		0b00001000
# define L_ARROW_PRESS	0b00010000
# define R_ARROW_PRESS	0b00100000
# define RESET			0b00000000

typedef unsigned int	t_uint;

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	int			w;
	int			h;
}				t_win;

typedef struct	s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_texture
{
	t_image		img;
	int			w;
	int			h;
}				t_texture;

typedef struct	s_sprite
{
	t_texture	tex;
	int			w;
	int			h;
}				t_sprite;

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_point_i
{
	int			x;
	int			y;
}				t_point_i;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_player
{
	t_point		pos;
	t_vector	dir;
	t_vector	cam_plane;
}				t_player;

typedef struct	s_raycast
{
	int			draw_start;
	int			draw_end;
	int			wall_height;
	int			side_map;
	double		dist_to_wall;
	t_point		delta_dist;
	t_point		dist_to_side;
	t_point		step;
}				t_raycast;

typedef struct	s_game
{
	t_uint		press_flags;
	t_win		win;
	t_image		img;
	t_player	plr;
	t_raycast	rcast;
	t_texture	tex_n;
	t_texture	tex_s;
	t_texture	tex_w;
	t_texture	tex_e;
	t_sprite	spr;
	int			color_ceil;
	int			color_floor;
	char		**map;
	size_t		img_size;
}				t_game;

int		init_cube(t_game *game, t_opt *opt);
void	ft_cube(t_game *game);

// paint
int		get_color(int t, int r, int g, int b);
void	ft_pixel_put(t_image *img, int x, int y, int color);
void	draw_ceil(t_game *game, int x);
void	draw_floor(t_game *game, int x);
// end paint
// hooks
int		win_close(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		render_frame(t_game *game);
// end hooks
// raycast
void	ft_raycast(t_game *game);
void	draw_line_wall(t_game *game, t_vector *ray, int x);
// end raycast

#endif
