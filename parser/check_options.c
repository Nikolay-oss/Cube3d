/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:42:20 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 17:19:56 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"

int	check_r(t_opt *opt, char *param)
{
	char	**resolution;
	size_t	count;
	size_t	digit_count[2];

	if (opt->r[2])
		return (6);
	resolution = ft_split(param, ' ');
	if (!resolution)
		return (7);
	count = 0;
	while (*(resolution + count))
		count++;
	if (count != 2)
		return (split_line_free(resolution, 7));
	else if (!check_digit(resolution, digit_count))
		return (split_line_free(resolution, 7));
	correct_resolution(opt, digit_count, resolution);
	opt->r[2] = 1;
	opt->count++;
	split_line_free(resolution, 1);
	return (0);
}

int	check_path_opt(t_opt *opt, char **option, char *param)
{
	if (*option)
		return (6);
	if (!check_ext(param, ".xpm"))
		return (2);
	*option = ft_strtrim(param, " ");
	if (!*option)
	{
		free(*option);
		return (5);
	}
	opt->count++;
	return (0);
}

static char	**check_color_line(char *line)
{
	char	**params;
	int		count;

	count = check_comma(line);
	if (count > 2 || count < 2)
		return (NULL);
	params = ft_split(line, ',');
	if (!params)
		return (NULL);
	return (params);
}

static t_bool	check_nbrs(char **params)
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
		ft_loop_digits(params, &i, &j, &count);
		j += skip_spaces(*(params + i) + j);
		if (*(*(params + i) + j) && *(*(params + i) + j) != ' ')
			return (1);
		else if (count > 3 || (!count && !zero_count))
			return (1);
		i++;
	}
	return (0);
}

int	check_color_opt(t_opt *opt, int *option, char *param)
{
	char	**color_map;
	int		count;

	if (option[3])
		return (6);
	color_map = check_color_line(param);
	if (!color_map)
		return (8);
	count = 0;
	while (*(color_map + count))
		count++;
	if (count != 3)
		return (split_line_free(color_map, 8));
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
