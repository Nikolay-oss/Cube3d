/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 04:18:40 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 06:38:36 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "handler_errors.h"

t_bool	compare_strsymbs(const char *str, const char *str_cmp,
						const size_t strcmp_size)
{
	size_t	i;

	i = 0;
	while (*(str + i))
	{
		if (!ft_memchr(str_cmp, *(str + i), strcmp_size))
			return (0);
		i++;
	}
	return (1);
}

static void	check_map_borders(t_opt *opt)
{
	if (!compare_strsymbs(*opt->map.map, " 1", 2))
		exit_error(9, opt, NULL, NULL);
	if (!compare_strsymbs(*(opt->map.map + opt->map.rows - 1), " 1", 2))
		exit_error(9, opt, NULL, NULL);
}

static void	follow_linemap(t_opt *opt, const char **map, size_t row_idx,
	size_t *sprites_count)
{
	size_t		j;
	size_t		str_sizes[3];
	const char	*str_curr;

	str_curr = *(map + row_idx);
	str_sizes[0] = ft_strlen(*(map + row_idx - 1));
	str_sizes[1] = ft_strlen(str_curr);
	str_sizes[2] = ft_strlen(*(map + row_idx + 1));
	j = 0;
	while (*(str_curr + j))
	{
		if (*(str_curr + j) == '0')
			check_around_02plr(opt, (const size_t *)str_sizes, row_idx, j);
		else if (*(str_curr + j) == '2')
		{
			check_around_02plr(opt, (const size_t *)str_sizes, row_idx, j);
			(*sprites_count)++;
		}
		else if (ft_memchr("NSWE", *(str_curr + j), 4))
		{
			check_around_02plr(opt, (const size_t *)str_sizes, row_idx, j);
			save_player_position(opt, *(str_curr + j), row_idx, j);
		}
		j++;
	}
}

static t_point	*save_sprite_positions(t_opt *opt, size_t sprites_count)
{
	t_point		*sprite_positions;
	size_t		i;
	size_t		j;

	if (!sprites_count)
		return (NULL);
	sprite_positions = (t_point *)ft_calloc(sprites_count, sizeof(t_point));
	if (!sprite_positions)
		exit_error(5, opt, NULL, NULL);
	i = 0;
	while (i < opt->map.rows)
	{
		j = 0;
		while (*(*(opt->map.map + i) + j))
		{
			if (*(*(opt->map.map + i) + j) == '2')
			{
				(sprite_positions + --sprites_count)->x = (double)i + 0.5;
				(sprite_positions + sprites_count)->y = (double)j + 0.5;
			}
			j++;
		}
		i++;
	}
	return (sprite_positions);
}

void	map_parser(t_opt *opt)
{
	size_t	i;
	size_t	sprites_count;

	if (!opt->map.rows)
		exit_error(11, opt, NULL, NULL);
	check_map_borders(opt);
	sprites_count = 0;
	i = 1;
	while (i < opt->map.rows - 1)
	{
		follow_linemap(opt, (const char **)opt->map.map, i, &sprites_count);
		i++;
	}
	if (opt->plr.pos.x < 1)
		exit_error(13, opt, NULL, NULL);
	opt->spr_positions = save_sprite_positions(opt, sprites_count);
	opt->sprites_count = sprites_count;
}