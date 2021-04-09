/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:07:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 20:06:47 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "ft_paint.h"
#include <math.h>

static void	draw_col_tex(t_game *game, t_texture *tex, double wallx, int x)
{
	t_point_i	tex_pos;
	double		step_tex;
	double		st_tex_pos;
	int			y;
	int			color;

	tex_pos.x = (int)(wallx * (double)tex->w);
	step_tex = (double)tex->h / game->rcast.wall_height;
	st_tex_pos = (game->rcast.draw_start - game->win.h / 2 +
		game->rcast.wall_height / 2) * step_tex;
	y = game->rcast.draw_start;
	while (y < game->rcast.draw_end)
	{
		tex_pos.y = st_tex_pos;
		st_tex_pos += step_tex;
		color = *(unsigned int*)(tex->img.addr + (tex_pos.y *
			tex->img.line_length + tex_pos.x * (tex->img.bits_per_pixel / 8)));
		ft_pixel_put(&game->img, x, y, color);
		y++;
	}
}

static void	choice_tex(t_game *game, t_vector *ray, t_texture *tex)
{
	if (ray->x < 0 && !game->rcast.side_map)
		*tex = game->tex_n;
	else if (ray->x > 0 && !game->rcast.side_map)
		*tex = game->tex_s;
	else if (ray->y < 0 && game->rcast.side_map)
		*tex = game->tex_e;
	else
		*tex = game->tex_w;
}

void		draw_line_wall(t_game *game, t_vector *ray, int x)
{
	double		wallx;
	t_texture	tex;

	if (!game->rcast.side_map)
		wallx = game->plr.pos.y + game->rcast.dist_to_wall * ray->y;
	else
		wallx = game->plr.pos.x + game->rcast.dist_to_wall * ray->x;
	wallx -= floor(wallx);
	choice_tex(game, ray, &tex);
	draw_col_tex(game, &tex, wallx, x);
}
