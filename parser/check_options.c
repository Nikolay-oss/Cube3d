/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:42:20 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 17:34:39 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"
#include <stdio.h>

int				check_r(t_opt *opt, char *param)
{
	char	**resolution;
	int 	count;
	int 	digit_count;

	if (opt->r[2])
		return (6); // duplicate line
	if (!(resolution = ft_split(param, ' ')))
		return (5);
	count = 0;
	while (*(resolution + count))
		count++;
	digit_count = 0;
	if (count != 2)
		return (split_line_free(resolution, 7)); // error
	else if (!check_digit(resolution, &digit_count)) // rewrite!
		return (split_line_free(resolution, 7)); // error
	// добавить установку максимального разрешения, если подано разрешение больше максимального разрешения экрана
	while (count--)
		opt->r[count] = ft_atoi(*(resolution + count));
	opt->r[2] = 1;
	opt->count++;
	split_line_free(resolution, 1);
	return (0);
}

int				check_path_opt(t_opt *opt, char **option, char *param)
{
	if (*option)
		return (6);
	if (!check_ext(param, ".xpm"))
		return (2);
	if (!(*option = ft_strtrim(param, " ")))
	{
		free(*option);
		return (5);
	}
	opt->count++;
	return (0);
}

static	char	**check_color_line(char *line)
{
	char	**params;
	int		count;

	count = check_comma(line);
	if (count > 2 || count < 2)
		return (NULL);
	if (!(params = ft_split(line, ',')))
		return (NULL);
	return (params);
}

static	int		check_nbrs(char **params)
{
	int	i;
	int	j;
	int	count;
	int	zero_count;

	i = 0;
	while (*(params + i))
	{
		j = skip_spaces(*(params + i));
		zero_count = j;
		while (*(*(params + i) + j) == '0')
			j++;
		zero_count = j - zero_count;
		count = 0;
		while (ft_isdigit(*(*(params + i) + j)))
		{
			count++;
			j++;
		}
		j += skip_spaces(*(params + i) + j);
		if (*(*(params + i) + j) && *(*(params + i) + j) != ' ')
			return (1); //   invalid symbol
		else if (count > 3)
			return (1); // число больше 3 знаков, значит больше максимального 255
		else if (!count && !zero_count)
			return (1);
		i++;
	}
	return (0);
}

int				check_color_opt(t_opt *opt, int *option, char *param)
{
	char	**color_map;
	int		count;

	if (option[3])
		return (6);
	if (!(color_map = check_color_line(param)))
		return (5);
	count = 0;
	while (*(color_map + count))
		count++;
	if (count != 3)
		return (split_line_free(color_map, 8)); // invalid color
	if (check_nbrs(color_map))
		return (split_line_free(color_map, 8));
	while (count--)
	{
		option[count] = ft_atoi(*(color_map + count));
		if (option[count] > 255)
			return (split_line_free(color_map, 8));
	}
	option[3] = 1;
	opt->count++;
	split_line_free(color_map, 1);
	return (0);
}
