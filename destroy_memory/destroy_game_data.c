#include "destroy_memory.h"

static void		destroy_game_mem2(t_game *game)
{
	destroy_general_memory(game->map, game->spr.positions);
	destroy_sptite_memory(game);
	free(game);
	game = NULL;
}

void		destroy_game_mem(t_game *game)
{
	if (!game)
		return ;
	if (game->tex_e.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_e.img.img);
	game->tex_e.img.img = NULL;
	if (game->tex_n.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_n.img.img);
	game->tex_n.img.img = NULL;
	if (game->tex_s.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_s.img.img);
	game->tex_s.img.img = NULL;
	if (game->tex_w.img.img)
		mlx_destroy_image(game->win.mlx, game->tex_w.img.img);
	game->tex_w.img.img = NULL;
	if (game->spr.tex.img.img)
		mlx_destroy_image(game->win.mlx, game->spr.tex.img.img);
	game->spr.tex.img.img = NULL;
	if (game->img.img)
		mlx_destroy_image(game->win.mlx, game->img.img);
	game->img.img = NULL;
	if (game->win.win)
		mlx_destroy_window(game->win.mlx, game->win.win);
	game->win.win = NULL;
	destroy_game_mem2(game);
}
