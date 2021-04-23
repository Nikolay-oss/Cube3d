/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:14:51 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 23:34:58 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"

void	ft_loop_digits(char **params, int *i, int *j, int *count)
{
	while (ft_isdigit(*(*(params + *i) + *j)))
	{
		(*count)++;
		(*j)++;
	}
}

void	correct_resolution(t_opt *opt, const size_t *digit_count,
	char **resolution)
{
	if (digit_count[0] > 4)
		opt->r[0] = 10000;
	else
		opt->r[0] = ft_atoi(*resolution);
	if (digit_count[1] > 4)
		opt->r[1] = 10000;
	else
		opt->r[1] = ft_atoi(*(resolution + 1));
}
