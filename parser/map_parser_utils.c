/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:14:58 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 23:35:21 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "handler_errors.h"

void	check_around_02plr(t_opt *opt, const size_t *str_sizes, size_t i,
	size_t j)
{
	const char	**map;
	size_t		k;
	char		around_symbs[4];

	map = (const char **)opt->map.map;
	if (j == 0 || j == *(str_sizes + 1) - 1)
		exit_error(9, opt, NULL, NULL);
	if (j > *(str_sizes + 0) - 1 || j > *(str_sizes + 2) - 1)
		exit_error(9, opt, NULL, NULL);
	around_symbs[0] = *(*(map + i) + j - 1);
	around_symbs[1] = *(*(map + i) + j + 1);
	around_symbs[2] = *(*(map + i - 1) + j);
	around_symbs[3] = *(*(map + i + 1) + j);
	k = 0;
	while (k < 4)
	{
		if (!ft_memchr("012NSWE", around_symbs[k], 7))
			exit_error(9, opt, NULL, NULL);
		k++;
	}
}

static void	select_player_direction(t_player *plr, const char c)
{
	if (c == 'N')
	{
		plr->dir.x = -1;
		plr->dir.y = 0;
	}
	else if (c == 'S')
	{
		plr->dir.x = 1;
		plr->dir.y = 0;
	}
	else if (c == 'W')
	{
		plr->dir.x = 0;
		plr->dir.y = -1;
	}
	else
	{
		plr->dir.x = 0;
		plr->dir.y = 1;
	}
}

static void	select_camera_plane(t_player *plr, const char c)
{
	if (c == 'N')
	{
		plr->cam_plane.x = 0;
		plr->cam_plane.y = 0.66;
	}
	else if (c == 'S')
	{
		plr->cam_plane.x = 0;
		plr->cam_plane.y = -0.66;
	}
	else if (c == 'W')
	{
		plr->cam_plane.x = -0.66;
		plr->cam_plane.y = 0;
	}
	else
	{
		plr->cam_plane.x = 0.66;
		plr->cam_plane.y = 0;
	}
}

void	save_player_position(t_opt *opt, const char c, const size_t x,
	const size_t y)
{
	if (opt->plr.pos.x > 0)
		exit_error(12, opt, NULL, NULL);
	opt->plr.pos.x = (double)x + 0.5;
	opt->plr.pos.y = (double)y + 0.5;
	select_player_direction(&opt->plr, c);
	select_camera_plane(&opt->plr, c);
}
