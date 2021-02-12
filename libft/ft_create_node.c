/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:41:58 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/12 19:46:58 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_create_node(void *data)
{
	t_node *node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	node->content = data;
	node->next = NULL;
	return (node);
}
