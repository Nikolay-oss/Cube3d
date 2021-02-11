/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:55:23 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/11 19:00:00 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include <stdio.h>
#include "libft.h"

int	main(int ac, char **av)
{
	t_opt	opt;

	if (ac < 2)
		return (0);
	init_opt(&opt);
	ft_parser(&opt, *(av + 1));
	// 9223372036854775807
	// printf("%d\t%d\n", ft_atoi("9223372036854775819"), atoi("9223372036854775819"));
	// sleep(1000);
	return (0);
}
