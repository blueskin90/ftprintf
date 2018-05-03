/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:25:31 by toliver           #+#    #+#             */
/*   Updated: 2018/05/03 03:28:29 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			fill_buffer(t_env *env, char c, int i)
{
	while (i > 0)
	{
		env->buff[env->buffi] = c;
		i--;
		env->buffi++;
		buff_check(env);
	}
}

int				parse_pcsize(t_env *env, t_arg *arg)
{
	env->str++;
	flags_cleanup(arg);
	if (arg->width > 1 && !(arg->flags & 32))
		fill_buffer(env, (arg->flags & 8) ? '0' : ' ', arg->width - 1);
	env->buff[env->buffi] = '%';
	env->buffi++;
	if (arg->flags & 32)
		fill_buffer(env, ' ', arg->width - 1);
	return (0);
}
