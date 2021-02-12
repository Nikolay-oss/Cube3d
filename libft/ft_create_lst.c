/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:06:00 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/12 18:07:12 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_lst()
{
	t_list *lst;
	
	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	lst->head = NULL;
	lst->head = 0;
	return (lst);
}
