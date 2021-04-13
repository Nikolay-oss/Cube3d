/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:34 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/13 19:25:05 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNC_H
# define MATH_FUNC_H
# include "data_types.h"

double	ft_pow2(double arg);
void	transform_point(const t_game *game,
	const t_point *relative_spr_pos, t_point *tr_point);

#endif
