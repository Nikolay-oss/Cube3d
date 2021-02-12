/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:41:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/12 16:14:38 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "ft_parser.h"
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

int		check_line(t_opt *opt, char *param)
{
	if (!param)
		return (1);
	if (!ft_strncmp(param, "R ", 1))
		{opt->eflag = check_r(opt, param + 1);printf("|R|: resolution -> %d %d\n", opt->r[0], opt->r[1]);}
	else if (!ft_strncmp(param, "NO ", 2))
		{opt->eflag = check_path_opt(opt, &opt->no, param + 2);printf("|NO|: path -> <%s>\n", opt->no);}
	else if (!ft_strncmp(param, "SO ", 2))
		{opt->eflag = check_path_opt(opt, &opt->so, param + 2);printf("|SO|: path -> <%s>\n", opt->so);}
	else if (!ft_strncmp(param, "WE ", 2))
		{opt->eflag = check_path_opt(opt, &opt->we, param + 2);printf("|WE|: path -> <%s>\n", opt->we);}
	else if (!ft_strncmp(param, "EA ", 2))
		{opt->eflag = check_path_opt(opt, &opt->ea, param + 2);printf("|EA|: path -> <%s>\n", opt->ea);}
	else if (!ft_strncmp(param, "S ", 1))
		{opt->eflag = check_path_opt(opt, &opt->s, param + 1);printf("|S|: path -> <%s>\n", opt->s);}
	else if (!ft_strncmp(param, "F ", 1))
		{opt->eflag = check_color_opt(opt, opt->f, param + 1);printf("|F|: color -> %d, %d, %d\n", opt->f[0], opt->f[1], opt->f[2]);}
	else if (!ft_strncmp(param, "C ", 1))
		{opt->eflag = check_color_opt(opt, opt->c, param + 1);printf("|C|: color -> %d, %d, %d\n", opt->c[0], opt->c[1], opt->c[2]);}
	else
		check_symbs(opt, param); //  brain on, please
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

int		ft_parser(t_opt *opt, char *filename)
{
	char	*param;
	char	*line;
	int		fd;
	int		res;
	// int i;

	if (!check_ext(filename, ".cub"))
		exit_error(-1); // error
	if ((fd = open(filename, O_RDONLY)) < 0)
		exit_error(-1); // error
	// printf("|%d|\n", fd);
	while ((res = get_next_line(fd, &line)) > -1)
	{
		// if (!(params = ft_split(line, ' ')))
		if (!(param = ft_strtrim(line, " ")))
		{
			free(line);
			exit_error(-1); // error
		}
		if (opt->count != 8)
			check_line(opt, param);
		// i = 0;
		// while (*(params + i))
		// 	printf("%s ", *(params + i++));
		// printf("\n");
		// split_line_free(params);
		// check_line(opt, line + skip_spaces(line));
		free(param);
		free(line);
		if (opt->eflag)
			exit_error(opt->eflag);
		if (!res)
			break ;
	}
	if (res < 0)
		return (-1); // error
	close(fd);
	return (0);
}
