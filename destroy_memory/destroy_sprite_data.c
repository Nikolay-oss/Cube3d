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

void	destroy_sptite_memory(t_game *game)
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
