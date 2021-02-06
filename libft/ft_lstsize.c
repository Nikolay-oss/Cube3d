/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:41:36 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/04 04:33:54 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		size;

	if (!lst)
		return (0);
	size = 0;
	node = lst;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}
