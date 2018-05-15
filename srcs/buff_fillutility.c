/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillutility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 23:38:57 by toliver           #+#    #+#             */
/*   Updated: 2018/05/15 06:19:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				buff_padding(t_env *env, t_arg *arg, int width)
{
	int			i;

	i = -1;
	while (++i < width)
		buff_fillwith(env, (arg->flags & 8) ? '0' : ' ');
	return (1);
}

int				buff_fillwith(t_env *env, char c)
{
	env->buff[env->buffi] = c;
	env->buffi++;
	buff_check(env);
	return (1);
}

int				buff_fillwithnumber(t_env *env, char c, int i)
{
	while (i > 0)
	{
		env->buff[env->buffi] = c;
		env->buffi++;
		i--;
	}
	buff_check(env);
	return (1);
}

int				buff_fillwithstr(t_env *env, char *str)
{
	while (*str)
	{
		buff_fillwith(env, *str);
		str++;
	}
	return (1);
}

int				buff_fillnumber(t_env *env, int nbr)
{
	
}
