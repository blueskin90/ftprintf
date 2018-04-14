/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:33:14 by toliver           #+#    #+#             */
/*   Updated: 2018/04/02 00:02:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_apostropheflag(t_env *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 1;
	return (1);
}

void			flags_cleanup(t_arg *arg)
{
	if ((arg->flags & 8) && arg->cat == 0 && arg->prec != -1)
		arg->flags ^= 8;
	if ((arg->flags & 32) && (arg->flags & 8))  // flag == 0
		arg->flags ^= 8;
	if ((arg->flags & 16) && arg->flags & 4)  // flag == ' '
		arg->flags ^= 4;
//	if ((arg->flags & 8) && arg->type == 19)
//		arg->flags = (arg->flags ^ 8);
//	if ((arg->flags & 32) && arg->type == 19)
//		arg->flags = (arg->flags ^ 32);
//	if ((arg->flags & 4) && !(isoneof(arg->type, SIGNED) && (intmax_t)arg->arg >= 0))
//		arg->flags = (arg->flags ^ 4);
//	if ((arg->flags & 16) && !(isoneof(arg->type, SIGNED) && (intmax_t)arg->arg >= 0)
}
