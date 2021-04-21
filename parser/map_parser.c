/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 04:18:40 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 06:38:36 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "handler_errors.h"

t_bool	compare_symbs(const char *str, const char *str_cmp,
						const size_t strcmp_size)
{
	size_t	i;

	i = 0;
	while (*(str + i))
	{
		if (!ft_memchr(str_cmp, *(str + i), strcmp_size))
			return (0);
		i++;
	}
	return (1);
}

static void	check_map_borders(t_opt *opt)
{
	if (!compare_symbs(*opt->map.map, " 1", 2))
		exit_error(9, opt, NULL, NULL);
	if (!compare_symbs(*(opt->map.map + opt->map.rows - 1), " 1", 2))
		exit_error(9, opt, NULL, NULL);
}

void	map_parser(t_opt *opt)
{
	check_map_borders(opt);
}