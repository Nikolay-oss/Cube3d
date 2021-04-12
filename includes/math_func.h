/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:11:34 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/12 19:20:21 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNC_H
# define MATH_FUNC_H
# include "handler_errors.h"

double	ft_pow2(double arg);
t_point	*get_transform_point(const t_game const *game,
	const t_vector const *spr_dist);

#endif
