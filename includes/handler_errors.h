/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:55:23 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/12 17:57:37 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_ERRORS_H
# define HANDLER_ERRORS_H
# include "data_types.h"
# include "libft.h"

void	exit_error(const int code_error, t_opt *opt, t_game *game, t_list *lst);

#endif
