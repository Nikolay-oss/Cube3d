/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:28:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 17:43:36 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"

int		check_symbs(char *line)
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

int		split_line_free(char **strs, int errorcode)
{
	int	i;

	i = 0;
	while (*(strs + i))
		free(*(strs + i++));
	free(strs);
	return (errorcode);
}

// rewrite! принимать как строку и скипать нули. Посчитать кол-во цифр
int		check_digit(char **params, int *digit_count)
{
	int	i;
	int	j;

	i = 0;
	while (*(params + i))
	{
		j = 0;
		while (*(*(params + i) + j))
		{
			// while (*(*(params + i) + j) == '0')
			// 	j++;
			if (!ft_isdigit(*(*(params + i) + j)))
				return (0);
			j++;
		}
		*digit_count += j;
		i++;
	}
	return (1);
}

int		check_comma(char *str)
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
