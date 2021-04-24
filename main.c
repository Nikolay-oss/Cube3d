/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:55:23 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:12:02 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_cube.h"
#include "handler_errors.h"
#include "libft.h"

int	main(int ac, char **av)
{
	t_opt	*opt;
	t_game	*game;

	if (ac < 2 || ac > 3)
		exit_error(1, NULL, NULL, NULL);
	opt = (t_opt *)ft_calloc(1, sizeof(t_opt));
	if (!opt)
		exit_error(5, opt, NULL, NULL);
	init_opt(opt);
	ft_parser(opt, *(av + 1));
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_error(5, opt, game, NULL);
	init_cube(game, opt);
	if (ac == 3)
	{
		if (ft_strncmp(*(av + 2), "--save", 6))
			exit_error(14, NULL, game, NULL);
		ft_cube(game, 1);
	}
	ft_cube(game, 0);
	return (0);
}
