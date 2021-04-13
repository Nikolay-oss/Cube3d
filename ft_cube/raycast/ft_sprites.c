/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:53:06 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/13 20:04:21 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprites.h"
#include "math_func.h"
#include <stdio.h>

void	calc_dists2_to_sprites(t_game *game, const size_t spr_count)
{
	size_t	i;
	double	*distances;
	t_point	*plr_pos;
	t_point	*spr_positions;

	distances = game->spr.distances;
	plr_pos = &game->plr.pos;
	spr_positions = game->spr.positions;
	i = 0;
	while (i < spr_count)
	{
		*(distances + i) = ft_pow2(plr_pos->x - (spr_positions + i)->x) +
			ft_pow2(plr_pos->y - (spr_positions + i)->y);
		i++;
	}
}

void	correct_draw_borders(t_sprite *spr, t_point_i *win_size)
{
	if (spr->draw_start.y < 0)
		spr->draw_start.y = 0;
	if (spr->draw_end.y >= win_size->y)
		spr->draw_end.y = win_size->y - 1;
	if (spr->draw_start.x < 0)
		spr->draw_start.x = 0;
	if (spr->draw_end.x >= win_size->x)
		spr->draw_end.x = win_size->x - 1;
}

void	calc_sprite_drawing_borders(t_game *game, const t_point *tr_p)
{
	t_point_i	win_size;
	t_sprite	*spr;

	win_size.x = game->win.w;
	win_size.y = game->win.h;
	spr = &game->spr;
	spr->spr_scr_x = (int)((win_size.x / 2) * (1 + tr_p->x / tr_p->y));
	spr->spr_scr_size = abs((int)(win_size.y / tr_p->y));
	spr->draw_start.y = -spr->spr_scr_size / 2 + win_size.y / 2;
	spr->draw_end.y = spr->spr_scr_size / 2 + win_size.y / 2;
	spr->draw_start.x = -spr->spr_scr_size / 2 + spr->spr_scr_x;
	spr->draw_end.x = spr->spr_scr_size / 2 + spr->spr_scr_x;
	correct_draw_borders(&game->spr, &win_size);
}

void	init_matrix(double **matrix, const t_player *plr)
{
	matrix[0][0] = plr->cam_plane.x;
	matrix[1][0] = plr->cam_plane.y;
	matrix[0][1] = plr->dir.x;
	matrix[1][1] = plr->dir.y;
}

void	ft_sprites(t_game *game)
{
	size_t	i;
	t_point	tr_point;
	t_point	relative_spr_pos;

	calc_dists2_to_sprites(game, game->spr.count);
	ft_sort(game->spr.distances, game->spr.positions, game->spr.count);
	init_matrix(game->spr.matrix, &game->plr);
	i = 0;
	while (i < game->spr.count)
	{
		relative_spr_pos.x = (game->spr.positions + i)->x - game->plr.pos.x;
		relative_spr_pos.y = (game->spr.positions + i)->y - game->plr.pos.y;
		transform_point(game, &relative_spr_pos, &tr_point);
		calc_sprite_drawing_borders(game, &tr_point);
		draw_sprite(game, &game->spr, &tr_point);
		i++;
	}
}
