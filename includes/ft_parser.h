/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:19:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/23 23:36:59 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <unistd.h>
# include "data_types.h"

void			init_opt(t_opt *opt);
void			ft_parser(t_opt *opt, char *filename);
int				split_line_free(char **strs, int errorcode);
t_bool			check_ext(char *filename, const char *set);
int				check_r(t_opt *opt, char *param);
t_bool			check_symbs(char *line);
t_bool			check_digit(char **params, size_t *digit_count);
int				check_path_opt(t_opt *opt, char **option, char *param);
int				check_color_opt(t_opt *opt, int *option, char *line);
int				check_comma(char *str);
int				skip_spaces(char *line);
void			save_mapline(t_opt *opt, t_list *map_lines, char *line);
void			make_map(t_opt *opt, t_list *map_lines);
t_bool			compare_strsymbs(const char *str, const char *str_cmp,
					const size_t strcmp_size);
void			map_parser(t_opt *opt);
void			check_around_02plr(t_opt *opt, const size_t *str_sizes,
					size_t i, size_t j);
void			save_player_position(t_opt *opt, const char c, const size_t x,
					const size_t y);
void			ft_loop_digits(char **params, int *i, int *j, int *count);
void			correct_resolution(t_opt *opt, const size_t *digit_count,
					char **resolution);

#endif
