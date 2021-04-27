/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:34:22 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 02:13:47 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "handler_errors.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static void	fill_four_bytes(char *ft_screen, int data)
{
	*ft_screen = (char)data;
	*(ft_screen + 1) = (char)(data >> 8);
	*(ft_screen + 2) = (char)(data >> 16);
	*(ft_screen + 3) = (char)(data >> 24);
}

static void	fill_bmp_header(t_game *game, char *ft_screen,
	const size_t header_size)
{
	*ft_screen = 'B';
	*(ft_screen + 1) = 'M';
	fill_four_bytes(ft_screen + 2, (int)(header_size + game->img_size));
	*(ft_screen + 10) = (char)header_size;
}

static void	fill_dib_header(t_game *game, char *ft_screen)
{
	*(ft_screen + 14) = (char)40;
	fill_four_bytes(ft_screen + 18, game->win.w);
	fill_four_bytes(ft_screen + 22, game->win.h);
	*(ft_screen + 26) = 1;
	*(ft_screen + 28) = 32;
}

static void	fill_bitmap_data(t_game *game, char *ft_screen)
{
	t_uint	pixel;
	int		x_idx;
	int		y_idx;
	size_t	i;

	i = 54;
	y_idx = game->win.h - 1;
	while (y_idx >= 0)
	{
		x_idx = 0;
		while (x_idx < game->win.w)
		{
			pixel = *(t_uint *)(game->img.addr + (y_idx * game->img.line_length
						+ x_idx * game->img.bits_per_pixel / 8));
			*(ft_screen + i++) = (char)pixel;
			*(ft_screen + i++) = (char)(pixel >> 8);
			*(ft_screen + i) = (char)(pixel >> 16);
			x_idx++;
			i += 2;
		}
		y_idx--;
	}
}

void	make_screenshot(t_game *game, const char *screen_name)
{
	const size_t	header_size = 54;
	size_t			bmp_size;
	char			*ft_screen;
	int				fd;

	fd = open(screen_name, O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	if (fd < 0)
		exit_error(17, NULL, game, NULL);
	bmp_size = header_size + game->img_size;
	ft_screen = (char *)ft_calloc(bmp_size, sizeof(char));
	if (!ft_screen)
		exit_error(5, NULL, game, NULL);
	fill_bmp_header(game, ft_screen, header_size);
	fill_dib_header(game, ft_screen);
	fill_bitmap_data(game, ft_screen);
	write(fd, ft_screen, bmp_size);
	free(ft_screen);
	close(fd);
}
