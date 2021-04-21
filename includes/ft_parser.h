/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:19:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/21 06:38:22 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <unistd.h>
# include "libft.h"
# include "data_types.h"

void			init_opt(t_opt *opt);
void			ft_parser(t_opt *opt, char *filename);
int				split_line_free(char **strs, int errorcode);
int				check_ext(char *filename, const char *set);
int				check_r(t_opt *opt, char *param);
int				check_symbs(char *line);
int				check_digit(char **params, int *digit_count);
int				check_path_opt(t_opt *opt, char **option, char *param);
int				check_color_opt(t_opt *opt, int *option, char *line);
int				check_comma(char *str);
int				skip_spaces(char *line);
void			save_mapline(t_opt *opt, t_list *map_lines, char *line);
void			make_map(t_opt *opt, t_list *map_lines);
t_bool			compare_symbs(const char *str, const char *str_cmp,
								const size_t strcmp_size);
void			map_parser(t_opt *opt);

#endif
