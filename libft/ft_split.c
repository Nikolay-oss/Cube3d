/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:04:17 by dkenchur          #+#    #+#             */
/*   Updated: 2020/11/04 04:21:51 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_words_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i + 1) != c && *(s + i + 1))
				i++;
		}
		i++;
	}
	return (count);
}

static void	split_free(char **strs)
{
	while (*strs)
	{
		free(*strs);
		strs++;
	}
	free(strs);
}

static void	split_words(char **strs, char const *s, int size, char c)
{
	char	*ptr;
	int		word_size;

	while (size--)
	{
		while (*s && *s == c)
			s++;
		ptr = ft_strchr(s, c);
		if (!ptr)
		{
			ptr = ft_strchr(s, '\0');
			word_size = ptr - s + 1;
		}
		else
			word_size = ptr - s + 1;
		if (!(*strs = (char*)malloc(word_size)))
		{
			split_free(strs);
			return ;
		}
		ft_strlcpy(*strs, s, word_size);
		strs++;
		s = ptr;
	}
	*strs = NULL;
}

char		**ft_split(char const *s, char c)
{
	char	**strs;
	int		words_count;

	if (!s)
		return (NULL);
	words_count = get_words_count(s, c);
	strs = (char**)malloc(sizeof(char*) * (words_count + 1));
	if (!strs)
		return (strs);
	split_words(strs, s, words_count, c);
	return (strs);
}
