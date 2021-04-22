/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:31:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 05:33:44 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "destroy_memory.h"
#include "handler_errors.h"

static t_bool	load_texture(t_texture *tex, void *mlx, char *path_to_tex)
{
	if (!(tex->img.img = mlx_xpm_file_to_image(mlx, path_to_tex, &tex->w,
		&tex->h)))
		return (0);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
		&tex->img.line_length, &tex->img.endian);
	return (1);
}

static t_bool	check_texs(t_game *game, t_opt *opt)
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
	if (!game->img.img)
		exit_error(5, NULL, game, NULL);
	game->img.addr = mlx_get_data_addr(game->img.img,
		&game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
}

void	ft_cube(t_game *game)
{
	game->win.win = mlx_new_window(game->win.mlx, game->win.w, game->win.h, "Cube3d");
	if (!game->win.win)
		exit_error(5, NULL, game, NULL);
	init_main_image(game);
	mlx_loop_hook(game->win.mlx, &render_frame, game);
	mlx_hook(game->win.win, 17, 0, &win_close, game); // macOS
	// mlx_hook(game->win.win, 33, 0, &win_close, game); // ubuntu
	mlx_hook(game->win.win, 2, 1L<<0, &key_press, game);
	mlx_hook(game->win.win, 3, 1L<<1, &key_release, game);
	mlx_loop(game->win.mlx);
}

void	init_cube(t_game *game, t_opt *opt)
{
	if (!(game->win.mlx = mlx_init()))
		exit_error(5, opt, game, NULL);
	if (!check_texs(game, opt))
		exit_error(3, opt, game, NULL);
	data_transfer(game, opt);
	destroy_options_mem(opt, 0);
}
