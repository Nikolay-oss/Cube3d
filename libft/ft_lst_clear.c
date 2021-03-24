/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:15:37 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/12 19:46:45 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_clear(t_list *lst, void (*del)(void*))
{
	t_node *current;
	t_node *node_old;

	if (!lst)
		return ;
	if (!lst->head)
	{
		free(lst);
		return ;
	}
	current = lst->head;
	while (current)
	{
		node_old = current->next;
		if (del)
			del(current->content);
		free(current);
		current = node_old;
	}
	free(lst);
}
