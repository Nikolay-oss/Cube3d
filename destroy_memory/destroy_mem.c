/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:50:35 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 05:35:48 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy_memory.h"
#include <stdio.h>

static void	destroy_map(char **map)
{
	size_t	i;

	if (!map)
		return ;
	i = 0;
	while (*(map + i))
		free(*(map + i++));
	free(map);
	map = NULL;
}

void		destroy_options_mem(t_opt *opt, int isfreemap)
{
	if (!opt)
		return ;
	if (opt->ea)
		free(opt->ea);
	opt->ea = NULL;
	if (opt->so)
		free(opt->so);
	opt->so = NULL;
	if (opt->no)
		free(opt->no);
	opt->no = NULL;
	if (opt->we)
		free(opt->we);
	opt->we = NULL;
	if (opt->s)
		free(opt->s);
	opt->s = NULL;
	if (isfreemap)
		destroy_map(opt->map.map);
	free(opt);
	opt = NULL;
}

void		destroy_game_mem(t_game *game)
{
	if (!game)
		return ;
	if (game->tex_e.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_e.img.img);
	game->tex_e.img.img = NULL;
	if (game->tex_n.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_n.img.img);
	game->tex_n.img.img = NULL;
	if (game->tex_s.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_s.img.img);
	game->tex_s.img.img = NULL;
	if (game->tex_w.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_w.img.img);
	game->tex_w.img.img = NULL;
	if (game->spr.tex.img.img)
		mlx_destroy_image(game->win.mlx, game->spr.tex.img.img);
	game->spr.tex.img.img = NULL;
	if (game->img.img)
		mlx_destroy_image(game->win.mlx, game->img.img);
	game->img.img = NULL;
	if (game->win.win)
		mlx_destroy_window(game->win.mlx, game->win.win);
	game->win.win = NULL;
	destroy_map(game->map);
	free(game);
	game = NULL;
}

void		destroy_all(t_opt *opt, t_game *game)
{
	if (opt)
		destroy_options_mem(opt, 0);
	if (game)
		destroy_game_mem(game);
}
