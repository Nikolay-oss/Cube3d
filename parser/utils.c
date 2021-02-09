/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:28:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/09 22:50:00 by dkenchur         ###   ########.fr       */
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

int		exit_error(char **params, int errorcode)
{
	split_line_free(params);
	return (errorcode);
}

int		check_digit(char **params)
{
	int	i;
	int	j;

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
		i++;
	}
	return (1);
}
