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
		return (0);
	init_opt(&opt);
	if (ft_parser(&opt, *(av + 1)) < 0)
		return (0);
	game = (t_game*)ft_calloc(1, sizeof(t_game));
	game->win.mlx = mlx_init();
	if (ac == 3)
		;
	else
	{
		if (init_cube(game, &opt) < 0)
		{
			free(game);
			// clear opt!
			return (0);
		}
	}
	mlx_loop(game->win.mlx);
	//sleep(1000);
	return (0);
}
