/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ident.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:17:09 by dkenchur          #+#    #+#             */
/*   Updated: 2021/02/09 21:31:17 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	init_ident(t_opt *ident)
{
	ident->r[0] = -1;
	ident->r[1] = -1;
	ident->r[2] = 0;
	ident->so = NULL;
	ident->no = NULL;
	ident->we = NULL;
	ident->ea = NULL;
	ident->s = NULL;
	ident->f[0] = -1;
	ident->f[1] = -1;
	ident->f[2] = -1;
	ident->f[3] = 0;
	ident->c[0] = -1;
	ident->c[1] = -1;
	ident->c[2] = -1;
	ident->c[3] = 0;
	ident->eflag = 0;
	ident->count = 0;
}
