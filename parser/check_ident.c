/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ident.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:42:20 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/08 22:19:41 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "libft.h"

void	check_r(t_ident *ident, char *str)
{
	char 	**params;
	int		count;

	params = ft_split(str, ' ');
	count = 0;
	while (*(params + count))
		count++;
	if (count != 2)
	{
		ident->eflag = 0;
		return ;
	}
	ident->r[0] = ft_atoi(*params);
	ident->r[1] = ft_atoi(*(params + 1));
	split_line_free(params);
}
