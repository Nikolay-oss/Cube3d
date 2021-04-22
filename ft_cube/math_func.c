/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:53:13 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/13 19:34:24 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"
#include <math.h>

double	ft_pow2(const double arg)
{
	return (arg * arg);
}

double	inverse_det2n2(const double **matrix)
{
	return (1 / (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]));
}

void	transform_point(const t_game *game,
	const t_point *relative_spr_pos, t_point *tr_point)
{
	const t_vector	*dir;
	const t_vector	*plane;
	double			inv_det;

	dir = &game->plr.dir;
	plane = &game->plr.cam_plane;
	inv_det = inverse_det2n2((const double **)game->spr.matrix);
	tr_point->x = inv_det * (dir->y * relative_spr_pos->x -
		dir->x * relative_spr_pos->y);
	tr_point->y = inv_det * (-plane->y * relative_spr_pos->x +
		plane->x * relative_spr_pos->y);
}

t_bool	isnear(t_point *spr_pos, t_point *plr_pos, double precision)
{
	double	delta_x;
	double	delta_y;

	delta_x = fabs(plr_pos->x - spr_pos->x);
	delta_y = fabs(plr_pos->y - spr_pos->y);
	if (delta_x < precision && delta_y < precision)
		return (1);
	return (0);
}
