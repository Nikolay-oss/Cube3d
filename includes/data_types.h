/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:49:16 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 05:41:31 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H
# include <stdlib.h>

# define ESC_U 65307
# define W_U 'w'
# define A_U 'a'
# define S_U 's'
# define D_U 'd'
# define L_ARROW_U 65361
# define R_ARROW_U 65363

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
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
typedef unsigned int	t_bool;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	int			w;
	int			h;
}				t_win;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_texture
{
	t_image		img;
	int			w;
	int			h;
}				t_texture;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_point_i
{
	int			x;
	int			y;
}				t_point_i;

typedef struct s_sprite
{
	t_texture	tex;
	double		*distances;
	double		*zbuf;
	t_point		*positions;
	t_point_i	draw_start;
	t_point_i	draw_end;
	size_t		count;
	double		**matrix;
	int			spr_scr_x;
	int			spr_scr_size;
}				t_sprite;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	t_point		pos;
	t_vector	dir;
	t_vector	cam_plane;
}				t_player;

typedef struct s_raycast
{
	int			draw_start;
	int			draw_end;
	int			wall_height;
	int			side_map;
	double		dist_to_wall;
	t_point		delta_dist;
	t_point		dist_to_side;
	t_point_i	step;
}				t_raycast;

typedef struct s_game
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

typedef struct s_map
{
	size_t	rows;
	char	**map;
}			t_map;

typedef struct s_opt
{
	int		r[3];
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	*s;
	int		f[4];
	int		c[4];
	t_map	map;
	int		eflag;
	int		count;
}				t_opt;

#endif
