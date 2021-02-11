/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:28:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/11 17:52:18 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"

void	check_symbs(t_opt *opt, char *line)
{
	if (*line && *line != ' ')
		opt->eflag = 1;
}

void	split_line_free(char **strs)
{
	int	i;

	i = 0;
	while (*(strs + i))
		free(*(strs + i++));
	free(strs);
}

void	exit_error(int errorcode)
{
	if (errorcode)
	{
		write(1, "ERROR\n", 6);
		exit(1);
	}
}

// rewrite! принимать как строку и скипать нули. Посчитать кол-во цифр
int		check_digit(char **params, int *digit_count)
{
	int	i;
	int	j;
	int k;

	i = 0;
	while (*(params + i))
	{
		j = 0;
		while (*(*(params + i) + j))
		{
			if (!ft_isdigit(*(*(params + i) + j)))
				return (0);
			j++;
		}
		*digit_count += j;
		i++;
	}
	return (1);
}
