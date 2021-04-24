/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:35:32 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 02:20:02 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include <math.h>

void	player_rotate(t_player *plr, const double rot_speed)
{
	double	dirx_old;
	double	planex_old;

	dirx_old = plr->dir.x;
	plr->dir.x = dirx_old * cos(rot_speed) - plr->dir.y * sin(rot_speed);
	plr->dir.y = dirx_old * sin(rot_speed) + plr->dir.y * cos(rot_speed);
	planex_old = plr->cam_plane.x;
	plr->cam_plane.x = planex_old * cos(rot_speed) - plr->cam_plane.y
		* sin(rot_speed);
	plr->cam_plane.y = planex_old * sin(rot_speed) + plr->cam_plane.y
		* cos(rot_speed);
}
