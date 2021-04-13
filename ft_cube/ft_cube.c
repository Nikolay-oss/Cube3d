/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:31:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/13 20:27:59 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "destroy_memory.h"
# include "handler_errors.h"
#include "ft_paint.h"
#include <stdio.h>

int		load_texture(t_texture *tex, void *mlx, char *path_to_tex)
{
	if (!(tex->img.img = mlx_xpm_file_to_image(mlx, path_to_tex, &tex->w,
		&tex->h)))
		return (0);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
		&tex->img.line_length, &tex->img.endian);
	return (1);
}

int		check_texs(t_game *game, t_opt *opt)
{
	if (!load_texture(&game->tex_s, game->win.mlx, opt->so))
		return (0);
	if (!load_texture(&game->tex_n, game->win.mlx, opt->no))
		return (0);
	if (!load_texture(&game->tex_w, game->win.mlx, opt->we))
		return (0);
	if (!load_texture(&game->tex_e, game->win.mlx, opt->ea))
		return (0);
	if (!load_texture(&game->spr.tex, game->win.mlx, opt->s))
		return (0);
	return (1);
}

void	init_main_image(t_game *game)
{
	game->img.img = mlx_new_image(game->win.mlx, game->win.w, game->win.h);
	game->img.addr = mlx_get_data_addr(game->img.img,
		&game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
}

void	ft_cube(t_game *game)
{
	game->win.win = mlx_new_window(game->win.mlx, game->win.w, game->win.h, "Cube3d");
	init_main_image(game);
	mlx_loop_hook(game->win.mlx, &render_frame, game);
	mlx_hook(game->win.win, 17, 0, &win_close, game); // macOS
	// mlx_hook(game->win.win, 33, 0, &win_close, game); // ubuntu
	mlx_hook(game->win.win, 2, 1L<<0, &key_press, game);
	mlx_hook(game->win.win, 3, 1L<<1, &key_release, game);
	mlx_loop(game->win.mlx);
}

int		init_cube(t_game *game, t_opt *opt)
{
	if (!(game->win.mlx = mlx_init()))
		exit_error(5, opt, game, NULL);//return (-1); // exit error
	if (!check_texs(game, opt))
		exit_error(3, opt, game, NULL);
	// set all parametrs after parser and choice game or screen
	game->win.w = opt->r[0];
	game->win.h = opt->r[1];
	game->color_ceil = get_color(0, opt->c[0], opt->c[1], opt->c[2]);	
	game->color_floor = get_color(0, opt->f[0], opt->f[1], opt->f[2]);
	game->img_size = (game->win.h - 0) * game->img.line_length +
		game->win.w * (game->img.bits_per_pixel / 8);
	game->map = opt->map;
	// game->plr.pos.x = 2.5;//11.5;
	// game->plr.pos.y = 2.5;//6.5;
	game->plr.pos.x = 11.5;
	game->plr.pos.y = 6.5;
	game->plr.dir.x = -0.99;
	game->plr.dir.y = 0;
	game->plr.cam_plane.x = 0;
	game->plr.cam_plane.y = 0.66;
	game->spr.count = 3;
	game->spr.distances = (double *)ft_calloc(game->spr.count, sizeof(double));
	game->spr.zbuf = (double *)ft_calloc(game->win.w, sizeof(double));
	game->spr.positions = (t_point *)ft_calloc(game->spr.count, sizeof(t_point));
	game->spr.positions[0].x = 9.5;
	game->spr.positions[0].y = 6.5;
	game->spr.positions[1].x = 9.5;
	game->spr.positions[1].y = 4.5;
	game->spr.positions[2].x = 9.5;
	game->spr.positions[2].y = 9.5;
	game->spr.matrix = (double **)ft_calloc(2, sizeof(double *));
	int i = 0;
	while (i < 2)
		*(game->spr.matrix + i++) = (double *)ft_calloc(2, sizeof(double));
	destroy_options_mem(opt, 0);
	return (1);
}
