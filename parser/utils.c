/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:28:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 21:34:14 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"

t_bool	check_symbs(char *line)
{
	size_t	i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	split_line_free(char **strs, int errorcode)
{
	size_t	i;

	i = 0;
	while (*(strs + i))
		free(*(strs + i++));
	free(strs);
	return (errorcode);
}

t_bool	check_digit(char **params, size_t *digit_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	digit_count[0] = 0;
	digit_count[1] = 0;
	while (*(params + i))
	{
		j = 0;
		while (*(*(params + i) + j))
		{
			while (*(*(params + i) + j) == '0' && !digit_count[i])
				j++;
			if (!ft_isdigit(*(*(params + i) + j)))
				return (0);
			else
				digit_count[i]++;
			j++;
		}
		i++;
	}
	return (1);
}

int	check_comma(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}
