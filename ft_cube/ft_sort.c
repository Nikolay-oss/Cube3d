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

void	ft_sort(double *distances, size_t count)
{
	double	tmp;
	t_bool	isswap;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		isswap = 0;
		while (j < count - i - 1)
		{
			if (ft_compare_descending(*(distances + j), *(distances + j + 1)))
			{
				tmp = *(distances + j);
				*(distances + j) = *(distances + j + 1);
				*(distances + j + 1) = tmp;
				isswap = 1;
			}
			j++;
		}
		if (!isswap)
			break ;
		i++;
	}
}
