/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:07:15 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/20 22:46:16 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#include "ft_paint.h"
#include "ft_sprites.h"
#include <math.h>
#include <stdio.h>

static void	choice_dir_x(t_game *game, t_vector *ray, t_point_i *ray_map)
{
	double	delta_dist_x;

	delta_dist_x = game->rcast.delta_dist.x;
	if (ray->x > 0)
	{
		game->rcast.step.x = 1;
		game->rcast.dist_to_side.x = (-game->plr.pos.x + ray_map->x + 1.0) *
			delta_dist_x;
	}
	else
	{
		game->rcast.step.x = -1;
		game->rcast.dist_to_side.x = (game->plr.pos.x - ray_map->x) *
			delta_dist_x;
	}
}

static void	choice_ray_dir(t_game *game, t_vector *ray, t_point_i *ray_map)
{
	double	delta_dist_y;

	delta_dist_y = game->rcast.delta_dist.y;
	if (ray->y > 0)
	{
		game->rcast.step.y = 1;
		game->rcast.dist_to_side.y = (-game->plr.pos.y + ray_map->y + 1.0) *
			delta_dist_y;
	}
	else
	{
		game->rcast.step.y = -1;
		game->rcast.dist_to_side.y = (game->plr.pos.y - ray_map->y) *
			delta_dist_y;
	}
	choice_dir_x(game, ray, ray_map);
}

static void	calc_walls_params(t_game *game, t_vector *ray, t_point_i *ray_map)
{
	double	*dist_to_wall;

	dist_to_wall = &game->rcast.dist_to_wall;
	if (game->rcast.side_map)
	{
		*dist_to_wall = (ray_map->y - game->plr.pos.y +
			(1 - game->rcast.step.y) / 2) / ray->y;
	}
	else
	{
		*dist_to_wall = (ray_map->x - game->plr.pos.x +
			(1 - game->rcast.step.x) / 2) / ray->x;
	}
	game->rcast.wall_height = (int)(game->win.h / *dist_to_wall);
	game->rcast.draw_start = -game->rcast.wall_height / 2 + game->win.h / 2;
	game->rcast.draw_end = game->rcast.wall_height / 2 + game->win.h / 2;
	if (game->rcast.draw_start < 0)
		game->rcast.draw_start = 0;
	if (game->rcast.draw_end >= game->win.h)
		game->rcast.draw_end = game->win.h - 1;
}

static void	find_ray_collision(t_game *game, t_vector *ray, t_point_i *ray_map)
{
	t_point	*dist_to_side;

	dist_to_side = &game->rcast.dist_to_side;
	while (1)
	{
		if (dist_to_side->x < dist_to_side->y)
		{
			dist_to_side->x += game->rcast.delta_dist.x;
			ray_map->x += game->rcast.step.x;
			game->rcast.side_map = 0;
		}
		else
		{
			dist_to_side->y += game->rcast.delta_dist.y;
			ray_map->y += game->rcast.step.y;
			game->rcast.side_map = 1;
		}
		// printf("x -> %d\t y -> %d\n", ray_map->x, ray_map->y);
		if (game->map[ray_map->x][ray_map->y] == '1')
			break ;
	}
	calc_walls_params(game, ray, ray_map);
}

void		ft_raycast(t_game *game)
{
	int			x;
	double		cam_plane;
	t_vector	ray;
	t_point_i	ray_map;

	x = 0;
	// printf("x -> %lf\ty -> %lf\n", game->plr.pos.x, game->plr.pos.y);
	while (x < game->win.w)
	{
		cam_plane = 2 * x / (double)game->win.w - 1;
		ray.x = game->plr.dir.x + game->plr.cam_plane.x * cam_plane;
		ray.y = game->plr.dir.y + game->plr.cam_plane.y * cam_plane;
		ray_map.x = (int)game->plr.pos.x;
		ray_map.y = (int)game->plr.pos.y;
		game->rcast.delta_dist.x = fabs(1 / ray.x);
		game->rcast.delta_dist.y = fabs(1 / ray.y);
		choice_ray_dir(game, &ray, &ray_map);
		find_ray_collision(game, &ray, &ray_map);
		draw_line_wall(game, &ray, x);
		draw_ceil(game, x);
		draw_floor(game, x);
		game->spr.zbuf[x] = game->rcast.dist_to_wall;
		x++;
	}
	ft_sprites(game);
}
