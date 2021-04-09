/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:20:07 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/26 19:34:45 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static void	move_forward(const char **map, t_player *plr, const double speed)
{
	if (map[(int)(plr->pos.x + plr->dir.x * speed)][(int)plr->pos.y] != '1')
		plr->pos.x += plr->dir.x * speed;
	if (map[(int)plr->pos.x][(int)(plr->pos.y + plr->dir.y * speed)] != '1')
		plr->pos.y += plr->dir.y * speed;
}

static void	move_backward(const char **map, t_player *plr, const double speed)
{
	if (map[(int)(plr->pos.x - plr->dir.x * speed)][(int)plr->pos.y] != '1')
		plr->pos.x -= plr->dir.x * speed;
	if (map[(int)plr->pos.x][(int)(plr->pos.y - plr->dir.y * speed)] != '1')
		plr->pos.y -= plr->dir.y * speed;
}

static void	move_left(const char **map, t_player *plr, const double speed)
{
	if (map[(int)(plr->pos.x - plr->dir.y * speed)][(int)plr->pos.y] != '1')
		plr->pos.x -= plr->cam_plane.x * speed;
	if (map[(int)plr->pos.x][(int)(plr->pos.y + plr->dir.x * speed)] != '1')
		plr->pos.y -= plr->cam_plane.y * speed;
}

static void	move_right(const char **map, t_player *plr, const double speed)
{
	if (map[(int)(plr->pos.x + plr->dir.y * speed)][(int)plr->pos.y] != '1')
		plr->pos.x += plr->cam_plane.x * speed;
	if (map[(int)plr->pos.x][(int)(plr->pos.y - plr->dir.x * speed)] != '1')
		plr->pos.y += plr->cam_plane.y * speed;
}

void		player_control(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.07;
	if (game->press_flags & W_PRESS)
		move_forward((const char**)game->map, &game->plr, move_speed);
	if (game->press_flags & A_PRESS)
		move_left((const char**)game->map, &game->plr, move_speed);
	if (game->press_flags & S_PRESS)
		move_backward((const char**)game->map, &game->plr, move_speed);
	if (game->press_flags & D_PRESS)
		move_right((const char**)game->map, &game->plr, move_speed);
	if (game->press_flags & L_ARROW_PRESS)
		player_rotate(&game->plr, rot_speed);
	if (game->press_flags & R_ARROW_PRESS)
		player_rotate(&game->plr, -rot_speed);
}
