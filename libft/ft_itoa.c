/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:11:09 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/03 23:41:01 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	init_size(int n)
{
	size_t	size;

	size = (n >= 0) ? 1 : 2;
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	long long int	num;
	char			*str;
	size_t			size;

	size = init_size(n);
	num = n;
	if (!(str = (char*)ft_calloc(size + 1, 1)))
		return (str);
	if (num < 0)
	{
		num *= -1;
		*str = '-';
	}
	while (size > 0)
	{
		*(str + --size) = (num % 10) + '0';
		num /= 10;
		if (*(str + size - 1) == '-' && size == 1)
			break ;
	}
	return (str);
}
