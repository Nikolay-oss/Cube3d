/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:53:10 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/13 14:51:28 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprites.h"

static t_bool	ft_compare_descending(double arg1, double arg2)
{
	return (arg1 < arg2);
}

static void	ft_swap_d(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_swap_points(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort(double *distances, t_point *pos, size_t count)
{
	t_bool	isswap;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		isswap = 0;
		while (j < count - i - 1)
		{
			if (ft_compare_descending(*(distances + j), *(distances + j + 1)))
			{
				ft_swap_d(distances + j, distances + j + 1);
				ft_swap_points(pos + j, pos + j + 1);
				isswap = 1;
			}
			j++;
		}
		if (!isswap)
			break ;
		i++;
	}
}
