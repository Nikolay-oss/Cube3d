#include "ft_cube.h"
#include "libft.h"

int	win_close(t_game *game)
{
	// destroy memory
	exit(1);
	return (0);
}

int	render_frame(t_game *game)
{
	ft_bzero(game->img.addr, game->img_size);
	// raycasting
	mlx_put_image_to_window(game->win.mlx, game->win.win, game->img.img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC || keycode == ESC_U)
		win_close(game);
	if (keycode == W || keycode == W_U)
		game->press_flags |= W_PRESS;
	if (keycode == A || keycode == A_U)
		game->press_flags |= A_PRESS;
	if (keycode == S || keycode == S_U)
		game->press_flags |= S_PRESS;
	if (keycode == D || keycode == D_U)
		game->press_flags |= D_PRESS;
	if (keycode == L_ARROW || keycode == L_ARROW_U)
		game->press_flags |= L_ARROW_PRESS;
	if (keycode == R_ARROW || keycode == R_ARROW_U)
		game->press_flags |= R_ARROW_PRESS;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W || keycode == W_U)
		game->press_flags &= ~1;
	if (keycode == A || keycode == A_U)
		game->press_flags &= ~(1 << 1);
	if (keycode == S || keycode == S_U)
		game->press_flags &= ~(1 << 2);
	if (keycode == D || keycode == D_U)
		game->press_flags &= ~(1 << 3);
	if (keycode == L_ARROW || keycode == L_ARROW_U)
		game->press_flags &= ~(1 << 4);
	if (keycode == R_ARROW || keycode == R_ARROW_U)
		game->press_flags &= ~(1 << 5);
	return (0);
}
