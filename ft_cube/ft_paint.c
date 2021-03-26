/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:07:43 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/26 18:40:05 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

int			get_color(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		ft_pixel_put(t_image *img, int x, int y, int color)
{
	char *dest;

	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

static void	draw_vertline(t_image *img, int x, int draw_range[2], int color)
{
	int y;

	y = draw_range[0];
	while (y < draw_range[1])
	{
		ft_pixel_put(img, x, y, color);
		y++;
	}
}

void		draw_floor(t_game *game, int x)
{
	int	draw_range[2];

	draw_range[0] = game->rcast.draw_end;
	draw_range[1] = game->win.h - 1;
	draw_vertline(&game->img, x, draw_range, game->color_floor);
}

void		draw_ceil(t_game *game, int x)
{
	int	draw_range[2];

	draw_range[0] = 0;
	draw_range[1] = game->rcast.draw_start;
	draw_vertline(&game->img, x, draw_range, game->color_ceil);
}
