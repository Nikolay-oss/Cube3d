/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:36:42 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 13:43:41 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprites.h"
#include "ft_paint.h"

static void	draw_col_sprite(const t_game *game, const t_sprite *spr,
	t_point_i *tex, const int x)
{
	int			color;
	int			d;
	int			y;

	y = spr->draw_start.y;
	while (y < spr->draw_end.y)
	{
		d = y * 256 - game->win.h * 128 + spr->spr_scr_size * 128;
		tex->y = (int)((d * spr->tex.h) / spr->spr_scr_size) / 256;
		color = *(unsigned int *)(spr->tex.img.addr + (tex->y * spr->tex.img.line_length +
			tex->x * (spr->tex.img.bits_per_pixel / 8)));
		if ((color & 0x00FFFFFF) != 0)
			ft_pixel_put(&((t_game*)(game))->img, x, y, color);
		y++;
	}
}

void	draw_sprite(const t_game *game, const t_sprite *spr,
	const t_point *tr_p)
{
	t_point_i	tex;
	int			x;

	x = spr->draw_start.x;
	while (x < spr->draw_end.x)
	{
		tex.x = (int)(256 * (x - (-spr->spr_scr_size / 2 + spr->spr_scr_x)) *
			spr->tex.w / spr->spr_scr_size) / 256;
		if (tr_p->y > 0 && x > 0 && x < game->win.w && tr_p->y < spr->zbuf[x])
			draw_col_sprite(game, spr, &tex, x);
		x++;
	}
}
