/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 04:52:24 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/09 20:08:13 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include "mlx.h"
# include "libft.h"
# include "data_types.h"


int		init_cube(t_game *game, t_opt *opt);
void	ft_cube(t_game *game);

// hooks
int		win_close(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		render_frame(t_game *game);
// end hooks
// raycast
void	ft_raycast(t_game *game);
// end raycast
// game control
void	player_control(t_game *game);
void	player_rotate(t_player *plr, const double rot_speed);
// end game control

// temp!
void	exit_error(const int code_error, t_opt *opt, t_game *game, t_list *lst);

#endif
