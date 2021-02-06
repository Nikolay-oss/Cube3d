/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 05:33:20 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/05 20:19:46 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*new_node;
	t_list	*node;

	list = NULL;
	new_node = NULL;
	if (!lst && f && del)
		return (list);
	node = lst;
	while (node)
	{
		if (!(new_node = ft_lstnew(f(node->content))))
		{
			ft_lstclear(&list, del);
			return (new_node);
		}
		ft_lstadd_back(&list, new_node);
		node = node->next;
	}
	return (list);
}
