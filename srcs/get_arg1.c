/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 00:27:04 by toliver           #+#    #+#             */
/*   Updated: 2018/05/15 06:19:39 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				get_int(t_env *env, t_arg *arg)
{
	arg->argument.i = va_arg(env->arg, int);
	return (1);
}

int				get_char(t_env *env, t_arg *arg)
{
	arg->argument.i = (char)va_arg(env->arg, int);
	return (1);
}

int				get_short(t_env *env, t_arg *arg)
{
	arg->argument.si = (short int)va_arg(env->arg, int);
	return (1);
}

int				get_long(t_env *env, t_arg *arg)
{
	arg->argument.li = va_arg(env->arg, long int);
	return (1);
}

int				get_longlong(t_env *env, t_arg *arg)
{
	arg->argument.lli = va_arg(env->arg, long long int);
	return (1);
}

int				get_intmaxt(t_env *env, t_arg *arg)
{
	arg->argument.imax = va_arg(env->arg, intmax_t);
	return (1);
}

int				get_sizet(t_env *env, t_arg *arg)
{
	arg->argument.siz = va_arg(env->arg, size_t);
	return (1);
}

int				get_ptrdifft(t_env *env, t_arg *arg)
{
	arg->argument.ptd = va_arg(env->arg, ptrdiff_t);
	return (1);
}

int				get_ldouble(t_env *env, t_arg *arg)
{
	arg->argument.ld = va_arg(env->arg, long double);
	return (1);
}

int				get_double(t_env *env, t_arg *arg)
{
	arg->argument.d = va_arg(env->arg, double);
	return (1);
}

int				get_wintt(t_env *env, t_arg *arg)
{
	arg->argument.wi = va_arg(env->arg, wint_t);
	return (1);
}

int				get_ptr(t_env *env, t_arg *arg)
{
	arg->argument.vptr = va_arg(env->arg, void*);
	return (1);
}
