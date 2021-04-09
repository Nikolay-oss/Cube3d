/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:55:23 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 20:16:56 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_cube.h"
#include "libft.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_opt	*opt;
	t_game	*game;

	if (ac < 2 || ac > 3)
		exit_error(1, NULL, NULL, NULL);
	if (!(opt = (t_opt*)ft_calloc(1, sizeof(t_opt))))
		exit_error(5, opt, NULL, NULL);
	init_opt(opt);
	ft_parser(opt, *(av + 1));
	if (!(game = (t_game*)ft_calloc(1, sizeof(t_game))))
		exit_error(5, opt, game, NULL);
	init_cube(game, opt);
	if (ac == 3)
		; // screen
	ft_cube(game);
	// sleep(1000);
	return (0);
}
