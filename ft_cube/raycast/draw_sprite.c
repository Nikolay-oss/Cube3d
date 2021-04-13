/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:36:42 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/13 20:21:52 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprites.h"
#include "ft_paint.h"

void	draw_sprite(const t_game *game, const t_sprite *spr,
	const t_point *tr_p)
{
	int			color;
	int			d;
	t_point_i	tex;
	size_t		x;
	size_t		y;

	x = spr->draw_start.x;
	while (x < spr->draw_end.x)
	{
		tex.x = (int)(256 * (x - (-spr->spr_scr_size / 2 + spr->spr_scr_x)) *
			spr->w / spr->spr_scr_size) / 256;
		if (tr_p->y > 0 && x > 0 && x < game->win.w && tr_p->y < spr->zbuf[x])
		{
			y = spr->draw_start.y;
			while (y < spr->draw_end.y)
			{
				d = (y - spr->v_move_scr) * 256 - game->win.h * 128 +
					spr->spr_scr_size * 128;
				tex.y = ((d * spr->h) / spr->spr_scr_size) / 256;
				color = *(unsigned int *)(spr->tex.img.addr + (tex.y * spr->tex.img.line_length +
					tex.x * (spr->tex.img.bits_per_pixel / 8)));
				if ((color & 0x00FFFFFF) != 0)
					ft_pixel_put(&((t_game*)(game))->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}
