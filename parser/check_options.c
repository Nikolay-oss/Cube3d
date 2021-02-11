/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:42:20 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/11 19:03:09 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"
#include <stdio.h>

int		check_r(t_opt *opt, char **params)
{
	int count;
	int digit_count;

	if (opt->r[2])
		return ((opt->eflag = 1)); // error
	count = 0;
	while (*(params + count))
		count++;
	digit_count = 0;
	if (count != 3)
		return ((opt->eflag = 1)); // error
	else if (!check_digit(params + 1, &digit_count)) // rewrite!
		return ((opt->eflag = 1));
	// добавить установку максимального разрешения, если подано разрешение больше максимального разрешения экрана
	opt->r[0] = ft_atoi(*(params + 1));
	opt->r[1] = ft_atoi(*(params + 2));
	opt->r[2] = 1;
	opt->count++;
	printf("|%s|: x -> %d y -> %d\n", *params, opt->r[0], opt->r[1]);
	return (0);
}

int		check_path_opt(t_opt *opt, char **option, char **params)
{
	int		count;

	if (*option)
		return ((opt->eflag = 1));
	count = 0;
	while (*(params + count))
		count++;
	if (count != 2)
		return ((opt->eflag = 1));
	else if (!check_ext(*(params + 1), ".xpm"))
		return ((opt->eflag = 1));
	if (!(*option = ft_strdup(*(params + 1))))
		return ((opt->eflag = 1));
	opt->count++;
	printf("|%s|: path -> %s\n", *params, *option);
	return (0);
}

int		check_color_opt(t_opt *opt, int **option, char **params)
{
	if ((*option)[3])
		return (1);
	return (0);
}
