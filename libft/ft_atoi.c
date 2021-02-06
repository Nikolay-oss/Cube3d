/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:43:19 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/02 13:20:57 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	ft_issign(const char c)
{
	if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	long long int	res;
	int				i;
	int				sign;

	res = 0;
	sign = 1;
	i = 0;
	while (*(str + i) && ft_isspace(*(str + i)) && !ft_issign(*(str + i)))
		i++;
	if (*(str + i) == '-')
	{
		sign = -1;
		i++;
	}
	else if (*(str + i) == '+')
		i++;
	while (*(str + i) && ft_isdigit(*(str + i)))
	{
		if (res > 2147483647)
			return (sign == -1 ? 0 : -1);
		res = res * 10 + (*(str + i) - '0');
		i++;
	}
	return (sign * res);
}
