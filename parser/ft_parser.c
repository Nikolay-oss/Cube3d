/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:41:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/09 22:40:28 by dkenchur         ###   ########.fr       */
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

int		check_line(t_opt *opt, char *str)
{
	if (!ft_strncmp(str, "R  ", 2))
		opt->eflag = check_r(opt, str);
	else if (!ft_strncmp(str, "NO  ", 3))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "SO  ", 3))
		opt->eflag = check_so(opt, str);
	else if (!ft_strncmp(str, "WE  ", 3))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "EA  ", 3))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "S  ", 2))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "F  ", 2))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "C  ", 2))
		printf("%s\n", str);
	else
		check_symbs(opt, str);
	if (opt->eflag)
		printf("ERROR: eflag = 1\n"); // error
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
	char	*line;
	int		fd;
	int		res;

	if (!check_ext(filename, ".cub"))
		return (-1); // error
	if (!(fd = open(filename, O_RDONLY)))
		return (-1); // error
	// printf("|%d|\n", fd);
	while ((res = get_next_line(fd, &line)) > -1)
	{
		check_line(opt, line + skip_spaces(line));
		free(line);
		if (!res)
			break ;
	}
	if (res < 0)
		return (-1); // error
	close(fd);
	return (0);
}
