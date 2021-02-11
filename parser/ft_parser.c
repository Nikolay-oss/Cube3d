/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:41:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/11 18:55:44 by dkenchur         ###   ########.fr       */
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

int		check_line(t_opt *opt, char **params)
{
	if (!*params)
		return (1);
	if (!ft_strncmp(*params, "R", 2))
		opt->eflag = check_r(opt, params);
	else if (!ft_strncmp(*params, "NO", 3))
		opt->eflag = check_path_opt(opt, &opt->no, params);// printf("%s\n", *params);
	else if (!ft_strncmp(*params, "SO", 3))
		opt->eflag = check_path_opt(opt, &opt->so, params); // printf("%s\n", *params);
	else if (!ft_strncmp(*params, "WE", 3))
		opt->eflag = check_path_opt(opt, &opt->we, params);// printf("%s\n", *params);
	else if (!ft_strncmp(*params, "EA", 3))
		opt->eflag = check_path_opt(opt, &opt->ea, params);// printf("%s\n", *params);
	else if (!ft_strncmp(*params, "S", 2))
		opt->eflag = check_path_opt(opt, &opt->s, params);// printf("%s\n", *params);
	else if (!ft_strncmp(*params, "F", 2))
		printf("%s\n", *params);
	else if (!ft_strncmp(*params, "C", 2))
		printf("%s\n", *params);
	else
		check_symbs(opt, *params); //  brain on, please
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
	char	**params;
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
		if (!(params = ft_split(line, ' ')))
		{
			free(line);
			exit_error(-1);; // error
		}
		if (opt->count != 8)
			check_line(opt, params);
		// i = 0;
		// while (*(params + i))
		// 	printf("%s ", *(params + i++));
		// printf("\n");
		split_line_free(params);
		// check_line(opt, line + skip_spaces(line));
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
