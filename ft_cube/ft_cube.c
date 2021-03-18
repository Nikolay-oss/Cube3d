/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:31:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/18 14:51:55 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

int		load_texture(t_texture *tex, void *mlx, char *path_to_tex)
{
	if (!(tex->img.img = mlx_xpm_file_to_image(mlx, path_to_tex, &tex->w,
		&tex->h)))
		return (-1);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
		&tex->img.line_length, &tex->img.endian);
	return (1);
}

int		check_texs(t_game *game, t_opt *opt)
{
	if (load_texture(&game->tex_s, game->win.mlx, opt->so) < 0)
		return (-1);
	if (load_texture(&game->tex_n, game->win.mlx, opt->no) < 0)
		return (-1);
	if (load_texture(&game->tex_w, game->win.mlx, opt->we) < 0)
		return (-1);
	if (load_texture(&game->tex_e, game->win.mlx, opt->ea) < 0)
		return (-1);
	if (load_texture(&game->spr.tex, game->win.mlx, opt->s) < 0)
		return (-1);
	return (1);
}

int		ft_cube(t_game *game)
{
	game->win.win = mlx_new_window(game->win.mlx, game->win.w, game->win.h, "Cube3d");
	// mlx_hook(game->win.win, 17, 0, fun, game); // macOS
	// mlx_hook(game->win.win, 33, 0, fun, game); // ubuntu
	// mlx_hook(game->win.win, 2, 1L<<0, fun, game);
	// mlx_loop_hook(game->win.mlx, fun, game);
}

int		init_cube(t_game *game, t_opt *opt)
{
	if (check_texs(game, opt) < 0)
		return (-1);
	// set all parametrs after parser and choice game or screen
	// delete!!!!
	game->win.w = opt->r[0];
	game->win.h = opt->r[1];
	
	// --------------
	return (1);
}
