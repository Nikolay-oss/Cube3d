/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:41:08 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/08 22:14:15 by dkenchur         ###   ########.fr       */
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

int		check_line(t_ident *ident, char *str)
{
	int i;

	i = 0;
	ident->r[1] = 0; // чтоб компилятор не ругался
	// printf("%s\n", *str);
	// while (*(str + i))
	// 	printf("%s ", *(str + i++));
	// printf("\n");
	// printf("|%d|\n", i);
	if (!ft_strncmp(str, "R  ", 2))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "NO  ", 3))
		printf("%s\n", str);
	else if (!ft_strncmp(str, "SO  ", 3))
		printf("%s\n", str);
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
	return (1);
}

void	split_line_free(char **strs)
{
	int	i;

	i = 0;
	while (*(strs + i))
		free(*(strs + i++));
	free(strs);
}

int		ft_parser(t_ident *ident, char *filename)
{
	char	*line;
	// char	**params;
	int		fd;
	int		res;

	if (!(fd = open(filename, O_RDONLY)))
		return (-1);
	// printf("|%d|\n", fd);
	while ((res = get_next_line(fd, &line)) > -1)
	{
		check_line(ident, line + skip_spaces(line));
		free(line);
		if (!res)
			break ;
	}
	if (res < 0)
		return (-1);
	close(fd);
	return (0);
}
