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

# define W 13
# define A 2
# define S 1
# define D 0
# define L_ARROW 123
# define R_ARROW 124

# define W_PRESS	0b00000001
# define A_PRESS	0b00000010
# define S_PRESS	0b00000100
# define D_PRESS	0b00001000
# define RESET		0b00000000

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

typedef struct	s_game
{
	t_uint		press_flags;
	t_win		win;
	t_image		img;
	t_player	plr;
	t_texture	tex_n;
	t_texture	tex_s;
	t_texture	tex_w;
	t_texture	tex_e;
	t_sprite	spr;
	int			color_ceil;
	int			color_floor;
}				t_game;

int		init_cube(t_game *game, t_opt *opt);

#endif
