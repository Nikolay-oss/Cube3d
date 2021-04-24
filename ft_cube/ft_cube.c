/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:31:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:51:27 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "destroy_memory.h"
#include "handler_errors.h"

static t_bool	load_texture(t_texture *tex, void *mlx, char *path_to_tex)
{
	tex->img.img = mlx_xpm_file_to_image(mlx, path_to_tex, &tex->w, &tex->h);
	if (!tex->img.img)
		return (0);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
			&tex->img.line_length, &tex->img.endian);
	return (1);
}

static t_bool	check_loaded_texs(t_game *game, t_opt *opt)
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
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	game->img_size = game->win.h * game->win.w
		* (game->img.bits_per_pixel / 8);
}

void	ft_cube(t_game *game, t_bool screen_flag)
{
	init_main_image(game);
	if (screen_flag)
	{
		ft_bzero(game->img.addr, game->img_size);
		ft_raycast(game);
		make_screenshot(game, "cub.bmp");
		win_close(game);
	}
	game->win.win = mlx_new_window(game->win.mlx, game->win.w, game->win.h,
			"Cube3d");
	if (!game->win.win)
		exit_error(5, NULL, game, NULL);
	mlx_loop_hook(game->win.mlx, &render_frame, game);
	mlx_hook(game->win.win, 17, 0, &win_close, game);
	mlx_hook(game->win.win, 2, 1L << 0, &key_press, game);
	mlx_hook(game->win.win, 3, 1L << 1, &key_release, game);
	mlx_loop(game->win.mlx);
}

void	init_cube(t_game *game, t_opt *opt)
{
	game->win.mlx = mlx_init();
	if (!game->win.mlx)
		exit_error(5, opt, game, NULL);
	if (!check_loaded_texs(game, opt))
		exit_error(3, opt, game, NULL);
	data_transfer(game, opt);
	destroy_options_mem(opt, 0);
}
