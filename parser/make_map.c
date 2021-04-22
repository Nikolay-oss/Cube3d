/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:12:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 06:38:53 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "handler_errors.h"
#include <stdio.h>

static t_bool	check_map_line(const char *line, size_t curr_idx)
{
	if (*(line + curr_idx) != '1')
		return (0);
	if (!compare_strsymbs(line + curr_idx, " 102NSWE", 8))
		return (0);
	return (1);
}

void	save_mapline(t_opt *opt, t_list *map_lines, char *line)
{
	size_t	curr_idx;

	curr_idx = (size_t)skip_spaces(line);
	if (!map_lines->size && !*(line + curr_idx))
	{
		free(line);
		return ;
	}
	if (!*(line + curr_idx))
	{
		ft_push_back(map_lines, NULL);
		return ;
	}
	if (!check_map_line(line, curr_idx))
		exit_error(9, opt, NULL, map_lines);
	if (map_lines->size > 0 && !map_lines->tail->content)
		exit_error(10, opt, NULL, map_lines);
	ft_push_back(map_lines, line);
}

void	make_map(t_opt *opt, t_list *map_lines)
{
	t_node	*node;
	char	**map;
	size_t	line_size;
	size_t	i;

	map = (char **)ft_calloc(map_lines->size + 1, sizeof(char *));
	if (!map)
		exit_error(5, opt, NULL, map_lines);
	i = 0;
	node = map_lines->head;
	while (i < map_lines->size && node->content)
	{
		line_size = ft_strlen((const char *)node->content);
		*(map + i) = (char *)ft_calloc(line_size + 1, sizeof(char));
		if (!*(map + i))
			exit_error(5, opt, NULL, map_lines);
		ft_strlcpy(*(map + i), (const char *)node->content, line_size + 1);
		node = node->next;
		i++;
	}
	opt->map.rows = i;
	*(map + i) = NULL;
	opt->map.map = map;
}
