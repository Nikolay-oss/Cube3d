/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:15:47 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 20:46:30 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "handler_errors.h"
#include "ft_paint.h"

static void	sprites_data_transfer(t_game *game, t_opt *opt)
{
	size_t	i;

	game->spr.count = opt->sprites_count;
	game->spr.positions = opt->spr_positions;
	game->spr.zbuf = (double *)ft_calloc(game->win.w, sizeof(double));
	if (!game->spr.zbuf)
		exit_error(5, opt, game, NULL);
	game->spr.distances = (double *)ft_calloc(game->spr.count, sizeof(double));
	if (!game->spr.distances)
		exit_error(5, opt, game, NULL);
	game->spr.matrix = (double **)ft_calloc(2, sizeof(double *));
	if (!game->spr.matrix)
		exit_error(5, opt, game, NULL);
	i = 0;
	while (i < 2)
	{
		*(game->spr.matrix + i) = (double *)ft_calloc(2, sizeof(double));
		if (!*(game->spr.matrix + i))
			exit_error(5, opt, game, NULL);
		i++;
	}
}

static void	player_data_transfer(t_game *game, t_opt *opt)
{
	game->plr.pos.x = opt->plr.pos.x;
	game->plr.pos.y = opt->plr.pos.y;
	game->plr.dir.x = opt->plr.dir.x;
	game->plr.dir.y = opt->plr.dir.y;
	game->plr.cam_plane.x = opt->plr.cam_plane.x;
	game->plr.cam_plane.y = opt->plr.cam_plane.y;
}

static void	graphic_data_transfer(t_game *game, t_opt *opt)
{
	int	height;
	int	width;

	game->win.w = opt->r[0];
	game->win.h = opt->r[1];
	mlx_get_screen_size(game->win.mlx, &width, &height);
	if (opt->r[0] > width)
		game->win.w = width;
	if (opt->r[1] > height)
		game->win.h = height;
	game->color_ceil = get_color(0, opt->c[0], opt->c[1], opt->c[2]);	
	game->color_floor = get_color(0, opt->f[0], opt->f[1], opt->f[2]);
	game->img_size = game->win.h * game->win.w *
		(game->img.bits_per_pixel / 8);
	game->map = opt->map.map;
}

void	data_transfer(t_game *game, t_opt *opt)
{
	graphic_data_transfer(game, opt);
	player_data_transfer(game, opt);
	sprites_data_transfer(game, opt);
}
