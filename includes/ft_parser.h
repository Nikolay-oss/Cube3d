/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:19:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/08 22:19:17 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <fcntl.h>
# include <unistd.h>

typedef	struct	s_ident
{
	int		r[2];
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	*s;
	int		f[3];
	int		c[3];
	int		eflag;
}				t_ident;

int		ft_parser(t_ident *ident, char *filename);
void	split_line_free(char **strs);

#endif