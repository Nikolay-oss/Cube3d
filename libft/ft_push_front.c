/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:44:30 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/12 19:46:36 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_front(t_list *begin, void *data)
{
	t_node *node;
	
	if (!(node = ft_create_node(data)))
		return ;
	if (!begin->head)
	{
		begin->head = node;
		begin->size++;
		return ;
	}
	node->next = begin->head;
	begin->head = node;
	begin->size++;
}
