/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:41:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/26 18:46:03 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_parser.h"
#include <fcntl.h>
#include <stdio.h>

int		skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (*line && *line == ' ')
	{
		line++;
		i++;
	}
	return (i);
}

int		check_options(t_opt *opt, char *param)
{
	if (!param)
		return (1);
	if (!ft_strncmp(param, "R  ", 2))
		{opt->eflag = check_r(opt, param + 1);printf("|R|: resolution -> %d %d\n", opt->r[0], opt->r[1]);}
	else if (!ft_strncmp(param, "NO  ", 3))
		{opt->eflag = check_path_opt(opt, &opt->no, param + 2);printf("|NO|: path -> <%s>\n", opt->no);}
	else if (!ft_strncmp(param, "SO  ", 3))
		{opt->eflag = check_path_opt(opt, &opt->so, param + 2);printf("|SO|: path -> <%s>\n", opt->so);}
	else if (!ft_strncmp(param, "WE  ", 3))
		{opt->eflag = check_path_opt(opt, &opt->we, param + 2);printf("|WE|: path -> <%s>\n", opt->we);}
	else if (!ft_strncmp(param, "EA  ", 3))
		{opt->eflag = check_path_opt(opt, &opt->ea, param + 2);printf("|EA|: path -> <%s>\n", opt->ea);}
	else if (!ft_strncmp(param, "S  ", 2))
		{opt->eflag = check_path_opt(opt, &opt->s, param + 1);printf("|S|: path -> <%s>\n", opt->s);}
	else if (!ft_strncmp(param, "F  ", 2))
		{opt->eflag = check_color_opt(opt, opt->f, param + 1);printf("|F|: color -> %d, %d, %d\n", opt->f[0], opt->f[1], opt->f[2]);}
	else if (!ft_strncmp(param, "C  ", 2))
		{opt->eflag = check_color_opt(opt, opt->c, param + 1);printf("|C|: color -> %d, %d, %d\n", opt->c[0], opt->c[1], opt->c[2]);}
	else
		opt->eflag = check_symbs(param); //  brain on, please!!!!!
	// printf("%d\n", ft_strncmp("NO    ./path/to_the/south/NO_texture.xpm", "NO ", 3));
	return (1);
}

int		check_ext(char *filename, const char *set)
{
	char *p_point;

	if (!(p_point = ft_strrchr(filename, '.')))
		return (0); // error
	if (ft_strncmp(p_point, set, 4) != 0)
		return (0); // error
	return (1);
}

void	check_line(t_opt *opt, t_list *map_lines, int fd, int *res)
{
	char	*line;
	char	*param;

	while ((*res = get_next_line(fd, &line)) > -1)
	{
		if (opt->count != 8)
		{
			if (!(param = ft_strtrim(line, " ")))
			{
				free(line);
				ft_lst_clear(map_lines, NULL);
				exit_error(-1); // error
			}
			check_options(opt, param);
			free(param);
			free(line);
		}
		else
			save_mapline(opt, map_lines, line);
		if (opt->eflag)
			exit_error(opt->eflag);
		if (!*res)
			break ;
	}
}

int		ft_parser(t_opt *opt, char *filename)
{
	int		fd;
	int		res;
	t_list	*map_lines;

	map_lines = ft_create_lst();
	if (!check_ext(filename, ".cub"))
		exit_error(-1); // error
	if ((fd = open(filename, O_RDONLY)) < 0)
		exit_error(-1); // error
	check_line(opt, map_lines, fd, &res);
	if (res < 0)
		return (-1); // error and destroy list
	close(fd);
	make_map(opt, map_lines);
	ft_lst_clear(map_lines, &free);
	return (0);
}
