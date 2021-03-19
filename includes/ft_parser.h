/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:19:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/03/18 07:31:08 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
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

void			init_opt(t_opt *opt);
int				ft_parser(t_opt *opt, char *filename);
int				split_line_free(char **strs, int errorcode);
int				check_ext(char *filename, const char *set);
int				check_r(t_opt *opt, char *param);
void			check_symbs(t_opt *opt, char *line);
int				check_digit(char **params, int *digit_count);
int				check_path_opt(t_opt *opt, char **option, char *param);
int				check_color_opt(t_opt *opt, int *option, char *line);
void			exit_error(int errorcode);
int				check_comma(char *str);
int				skip_spaces(char *line);

#endif
