/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 04:52:24 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/24 21:33:40 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include "mlx.h"
# include "libft.h"
# include "data_types.h"

void	init_cube(t_game *game, t_opt *opt);
void	ft_cube(t_game *game, t_bool screen_flag);
int		win_close(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		render_frame(t_game *game);
void	ft_raycast(t_game *game);
void	player_control(t_game *game);
void	player_rotate(t_player *plr, const double rot_speed);
void	data_transfer(t_game *game, t_opt *opt);
void	make_screenshot(t_game *game, const char *screen_name);

#endif
