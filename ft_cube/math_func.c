/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:53:13 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/12 19:20:15 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

double	ft_pow2(const double arg)
{
	return (arg * arg);
}

double	inverse_det2n2(const double const **matrix)
{
	return (1 / (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]));
}

t_point	*get_transform_point(const t_game const *game,
	const t_vector const *spr_dist)
{
	t_point		*tr_point;
	t_vector	*dir;
	t_vector	*plane;
	double		inv_det;

	tr_point = (t_point *)ft_calloc(1, sizeof(t_point));
	if (!tr_point)
		exit_error(5, NULL, game, NULL);
	dir = &game->plr.dir;
	plane = &game->plr.cam_plane;
	inv_det = inverse_det2n2(game->spr.matrix);
	tr_point->x = inv_det * (dir->y * spr_dist->x - dir->x * spr_dist->y);
	tr_point->y = inv_det * (-plane->y * spr_dist->x + plane->x * spr_dist->y);
	return (tr_point);
}
