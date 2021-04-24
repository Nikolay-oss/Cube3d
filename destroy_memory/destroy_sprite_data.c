/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_sprite_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:15:35 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 02:18:30 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy_memory.h"

static void	destroy_matrix(double **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < 2)
		free(*(matrix + i++));
	free(matrix);
	matrix = NULL;
}

void	destroy_sprite_memory(t_game *game)
{
	destroy_matrix(game->spr.matrix);
	if (game->spr.distances)
		free(game->spr.distances);
	game->spr.distances = NULL;
	if (game->spr.zbuf)
		free(game->spr.zbuf);
	game->spr.zbuf = NULL;
	game->spr.positions = NULL;
}
