/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:10:58 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/12 19:46:41 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_back(t_list *begin, void *data)
{
	t_node *new;
	t_node *current;
	
	if (!(new = ft_create_node(data)))
		return ;
	if (!begin->head)
	{
		begin->head = new;
		begin->size++;
		return ;
	}
	current = begin->head;
	while (current->next)
		current = current->next;
	current->next = new;
	begin->size++;
}
