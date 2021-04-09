/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_memory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:55:46 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 19:58:49 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_MEMORY_H
# define DESTROY_MEMORY_H
# include "data_types.h"
# include "mlx.h"

void	destroy_options_mem(t_opt *opt, int isfreemap);
void	destroy_game_mem(t_game *game);
void	destroy_all(t_opt *opt, t_game *game);

#endif
