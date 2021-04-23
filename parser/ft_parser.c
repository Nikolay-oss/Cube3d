/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:41:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 23:33:27 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_parser.h"
#include "handler_errors.h"
#include <fcntl.h>

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (*(line + i) && *(line + i) == ' ')
		i++;
	return (i);
}

void	check_options(t_opt *opt, char *param)
{
	if (!param)
		return ;
	if (!ft_strncmp(param, "R  ", 2))
		opt->eflag = check_r(opt, param + 1);
	else if (!ft_strncmp(param, "NO  ", 3))
		opt->eflag = check_path_opt(opt, &opt->no, param + 2);
	else if (!ft_strncmp(param, "SO  ", 3))
		opt->eflag = check_path_opt(opt, &opt->so, param + 2);
	else if (!ft_strncmp(param, "WE  ", 3))
		opt->eflag = check_path_opt(opt, &opt->we, param + 2);
	else if (!ft_strncmp(param, "EA  ", 3))
		opt->eflag = check_path_opt(opt, &opt->ea, param + 2);
	else if (!ft_strncmp(param, "S  ", 2))
		opt->eflag = check_path_opt(opt, &opt->s, param + 1);
	else if (!ft_strncmp(param, "F  ", 2))
		opt->eflag = check_color_opt(opt, opt->f, param + 1);
	else if (!ft_strncmp(param, "C  ", 2))
		opt->eflag = check_color_opt(opt, opt->c, param + 1);
	else
		opt->eflag = check_symbs(param);
}

t_bool	check_ext(char *filename, const char *set)
{
	char	*p_point;

	p_point = ft_strrchr(filename, '.');
	if (!p_point)
		return (0);
	if (ft_strncmp(p_point, set, 4) != 0)
		return (0);
	return (1);
}

void	check_line(t_opt *opt, t_list *map_lines, int fd, int *res)
{
	char	*line;
	char	*param;

	*res = get_next_line(fd, &line);
	while (*res > -1)
	{
		if (opt->count != 8)
		{
			param = ft_strtrim(line, " ");
			if (!param)
			{
				free(line);
				ft_lst_clear(map_lines, NULL);
				exit_error(5, opt, NULL, NULL);
			}
			check_options(opt, param);
			free(param);
			free(line);
		}
		else
			save_mapline(opt, map_lines, line);
		if (!*res || opt->eflag)
			break ;
	}
}

void	ft_parser(t_opt *opt, char *filename)
{
	int		fd;
	int		res;
	t_list	*map_lines;

	map_lines = ft_create_lst();
	if (!map_lines)
		exit_error(5, opt, NULL, NULL);
	if (!check_ext(filename, ".cub"))
		exit_error(2, opt, NULL, map_lines);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error(3, opt, NULL, map_lines);
	check_line(opt, map_lines, fd, &res);
	if (opt->eflag)
		exit_error(opt->eflag, opt, NULL, map_lines);
	if (res < 0)
		exit_error(4, opt, NULL, map_lines);
	close(fd);
	make_map(opt, map_lines);
	map_parser(opt);
	ft_lst_clear(map_lines, &free);
}
