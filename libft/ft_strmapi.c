/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:48:22 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/02 21:02:44 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			size;
	char			*str;

	if (!s)
		return ((char*)s);
	i = 0;
	size = ft_strlen(s);
	if (!(str = ft_calloc(size + 1, 1)))
		return (str);
	while (*(s + i))
	{
		*(str + i) = f(i, (char)*(s + i));
		i++;
	}
	return (str);
}
