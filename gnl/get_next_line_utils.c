/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 23:41:52 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/24 21:49:14 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	ft_exit_code(int isexit, int res)
{
	if (!isexit && res > 0)
		return (1);
	if (res == -1)
		return (-1);
	else
		return (0);
}

int	fill_remainder(char **current, char **remainder, char **buf, int *isexit)
{
	*current = ft_strchr(*buf, '\n');
	if (*current)
	{
		**current = '\0';
		*remainder = ft_strdup(++(*current));
		if (!*remainder)
		{
			free(*buf);
			return (0);
		}
		*isexit = 0;
	}
	return (1);
}
