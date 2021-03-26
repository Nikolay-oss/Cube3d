/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:12:26 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/26 19:52:16 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include <stdio.h>

int		check_map_line(t_opt *opt, char *line)
{
	size_t	i;
	size_t	str_size;

	i = 0;
	str_size = ft_strlen(line);
	while (i < str_size)
	{
		if (!ft_memchr(" 1", *(line + i), 2))
			return (1);
		i++;
	}
	return (0);
}

void	save_mapline(t_opt *opt, t_list *map_lines, char *line)
{
	if (!map_lines->size && !check_symbs(line))
	{
		free(line);
		return ;
	}
	// check last map line
	// if ()
	ft_push_back(map_lines, line);
}

void	make_map(t_opt *opt, t_list *map_lines)
{
	t_node	*node;
	size_t	line_size;
	size_t	i;
	size_t	j;

	if (!(opt->map = (char**)ft_calloc(map_lines->size + 1, sizeof(char*))))
		return ; // destroy memory and exit
	i = 0;
	node = map_lines->head;
	while (i < map_lines->size)
	{
		line_size = ft_strlen((const char*)node->content);
		*(opt->map + i) = (char*)ft_calloc(line_size + 1, sizeof(char));
		if (!*(opt->map + i))
			return ; // destroy memory and exit
		j = 0;
		while (j < line_size)
		{
			*(*(opt->map + i) + j) = *(char*)(node->content + j);
			j++;
		}
		node = node->next;
		i++;
	}
	*(opt->map + i) = NULL;
}
