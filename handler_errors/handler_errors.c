/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:50:31 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 03:09:48 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy_memory.h"
#include "libft.h"
#include <stdio.h>

static void	select_error(const int code_error)
{
	if (code_error == 1)
		ft_putstr_fd("Error: Invalid args\n", 1);
	else if (code_error == 2)
		ft_putstr_fd("Error: Invalid file extension\n", 1);
	else if (code_error == 3 || code_error == 4 || code_error == 5)
		perror("Error");
	else if (code_error == 6)
		ft_putstr_fd("Error: Duplicate option\n", 1);
	else if (code_error == 7)
		ft_putstr_fd("Error: Invalid setting of option R\n", 1);
	else if (code_error == 8)
		ft_putstr_fd("Error: Invalid setting of option color\n", 1);
	else if (code_error == 9)
		ft_putstr_fd("Error: Invalid map\n", 1);
	else if (code_error == 10)
		ft_putstr_fd("Error: More than one map detected\n", 1);
}

void		exit_error(const int code_error, t_opt *opt, t_game *game, t_list *lst)
{
	destroy_all(opt, game);
	if (lst)
		ft_lst_clear(lst, &free);
	select_error(code_error);
	exit(1);
}
