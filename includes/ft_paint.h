/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:05:00 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 20:08:18 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAINT_H
# define FT_PAINT_H
# include "data_types.h"

int		get_color(int t, int r, int g, int b);
void	ft_pixel_put(t_image *img, int x, int y, int color);
void	draw_ceil(t_game *game, int x);
void	draw_floor(t_game *game, int x);
void	draw_line_wall(t_game *game, t_vector *ray, int x);

#endif
