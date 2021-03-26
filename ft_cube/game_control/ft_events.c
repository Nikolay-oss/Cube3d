/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:07:10 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/26 19:38:12 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "libft.h"

int	win_close(t_game *game)
{
	// destroy memory
	mlx_destroy_image(game->win.mlx, game->tex_e.img.img);
	mlx_destroy_image(game->win.mlx, game->tex_n.img.img);
	mlx_destroy_image(game->win.mlx, game->tex_s.img.img);
	mlx_destroy_image(game->win.mlx, game->tex_w.img.img);
	mlx_destroy_image(game->win.mlx, game->spr.tex.img.img);
	mlx_destroy_image(game->win.mlx, game->img.img);
	mlx_destroy_window(game->win.mlx, game->win.win);
	size_t i = 0;
	while (*(game->map + i))
		free(*(game->map + i++));
	free(game->map);
	free(game->win.mlx);
	free(game);
	exit(1);
	return (0);
}

int	render_frame(t_game *game)
{
	ft_bzero(game->img.addr, game->img_size);
	ft_raycast(game);
	player_control(game);
	mlx_put_image_to_window(game->win.mlx, game->win.win, game->img.img, 0, 0);
	mlx_do_sync(game->win.mlx);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC || keycode == ESC_U)
		win_close(game);
	if (keycode == W || keycode == W_U)
		game->press_flags |= W_PRESS;
	if (keycode == A || keycode == A_U)
		game->press_flags |= A_PRESS;
	if (keycode == S || keycode == S_U)
		game->press_flags |= S_PRESS;
	if (keycode == D || keycode == D_U)
		game->press_flags |= D_PRESS;
	if (keycode == L_ARROW || keycode == L_ARROW_U)
		game->press_flags |= L_ARROW_PRESS;
	if (keycode == R_ARROW || keycode == R_ARROW_U)
		game->press_flags |= R_ARROW_PRESS;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W || keycode == W_U)
		game->press_flags &= ~1;
	if (keycode == A || keycode == A_U)
		game->press_flags &= ~(1 << 1);
	if (keycode == S || keycode == S_U)
		game->press_flags &= ~(1 << 2);
	if (keycode == D || keycode == D_U)
		game->press_flags &= ~(1 << 3);
	if (keycode == L_ARROW || keycode == L_ARROW_U)
		game->press_flags &= ~(1 << 4);
	if (keycode == R_ARROW || keycode == R_ARROW_U)
		game->press_flags &= ~(1 << 5);
	return (0);
}
