/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:19:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/09 22:50:08 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <fcntl.h>
# include <unistd.h>

typedef	struct	s_opt
{
	int		r[3];
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	*s;
	int		f[4];
	int		c[4];
	int		eflag;
	int		count;
}				t_opt;

void	init_ident(t_opt *opt);
int		ft_parser(t_opt *opt, char *filename);
void	split_line_free(char **strs);
int		check_ext(char *filename, const char *set);
int		check_r(t_opt *opt, char *str);
void	check_symbs(t_opt *opt, char *line);
int		check_digit(char **params);
int		check_so(t_opt *opt, char *str);
int		exit_error(char **params, int errorcode);

#endif