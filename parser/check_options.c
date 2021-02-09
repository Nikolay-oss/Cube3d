/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:42:20 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/09 22:51:16 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"
#include <stdio.h>

int		check_r(t_opt *opt, char *str)
{
	char 	**params;
	int		count;

	if (opt->r[2])
		return (1);// error
	if (!(params = ft_split(str, ' ')))
		return (1);
	count = 0;
	while (*(params + count))
		count++;
	if (count != 3) // error
		return (exit_error(params, 1));
	else if (!check_digit(params + 1)) // error
		return (exit_error(params, 1));
	opt->r[0] = ft_atoi(*(params + 1));
	opt->r[1] = ft_atoi(*(params + 2));
	if (opt->r[0] <= 0 || opt->r[1] <= 0)
		return (exit_error(params, 1));
	split_line_free(params);
	opt->r[2] = 1;
	opt->count++;
	printf("|%s|: x -> %d y -> %d\n", str, opt->r[0], opt->r[1]);
	return (0);
}

int		check_so(t_opt *opt, char *str)
{
	char	**params;
	int		count;

	if (opt->so)
		return (1);
	if (!(params = ft_split(str, ' ')))
		return (1);
	count = 0;
	while (*(params + count))
		count++;
	if (count != 2)
		return (exit_error(params, 1));
	else if (!check_ext(*(params + 1), ".xpm"))
		return (exit_error(params, 1));
	if (!(opt->so = ft_strdup(*(params + 1))))
		return (exit_error(params, 1));
	split_line_free(params);
	opt->count++;
	printf("|%s|: path -> %s\n", str, opt->so);
	return (0);
}
