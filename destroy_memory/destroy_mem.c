/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:50:35 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 02:18:02 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy_memory.h"
#include <stdio.h>

static void	destroy_map(char **map)
{
	size_t	i;

	if (!map)
		return ;
	i = 0;
	while (*(map + i))
		free(*(map + i++));
	free(map);
	map = NULL;
}

void	destroy_general_memory(char **map, t_point *spr_positions)
{
	destroy_map(map);
	if (spr_positions)
		free(spr_positions);
	spr_positions = NULL;
}

void	destroy_options_mem(t_opt *opt, int isfree)
{
	if (!opt)
		return ;
	if (opt->ea)
		free(opt->ea);
	opt->ea = NULL;
	if (opt->so)
		free(opt->so);
	opt->so = NULL;
	if (opt->no)
		free(opt->no);
	opt->no = NULL;
	if (opt->we)
		free(opt->we);
	opt->we = NULL;
	if (opt->s)
		free(opt->s);
	opt->s = NULL;
	if (isfree)
		destroy_general_memory(opt->map.map, opt->spr_positions);
	free(opt);
	opt = NULL;
}

void	destroy_all(t_opt *opt, t_game *game)
{
	if (opt)
		destroy_options_mem(opt, 0);
	if (game)
		destroy_game_mem(game);
}
