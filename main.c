/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:55:23 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/18 14:31:55 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_cube.h"
#include "libft.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_opt	opt;
	t_game	*game;

	if (ac < 2 || ac > 3)
	{
		ft_putstr_fd("Invalid args\n", 0);
		return (1); // exit_error
	}
	init_opt(&opt);
	if (ft_parser(&opt, *(av + 1)) < 0)
		return (1); // exit_error
	if (!(game = (t_game*)ft_calloc(1, sizeof(t_game))))
		return (1); // exit_error
	init_cube(game, &opt);
	if (ac == 3)
		; // screen
	ft_cube(game);
	//sleep(1000);
	return (0);
}
