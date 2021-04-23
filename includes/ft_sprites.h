/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:20:54 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 23:37:15 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRITES_H
# define FT_SPRITES_H
# include "data_types.h"

void	ft_sprites(t_game *game);
void	ft_sort(double *distances, t_point *pos, size_t count);
void	draw_sprite(const t_game *game, const t_sprite *spr,
			const t_point *tr_p);

#endif
