/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 18:10:03 by toliver           #+#    #+#             */
/*   Updated: 2018/04/03 23:37:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdio.h>
void			arg_parse(t_env *env, t_arg *arg)
{
	(void)arg;
	(void)env;
}

void			get_arg(t_env *env, t_arg *arg) // gerer le cas du $
{
	if (env->get_arg[arg->cat][arg->length] == NULL)
		env->get_arg[arg->cat][0](env, arg);
	else
		env->get_arg[arg->cat][arg->length](env, arg);
}

int				parse_dsize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 1;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillint(env, arg);
	env->str++;
	return (0);
}

int				parse_Dsize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 1;
	arg->length = (arg->length < 3) ? 3 : arg->length;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillint(env, arg);
	env->str++;
	return (0);
}

int				parse_osize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 2;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filloct(env, arg);
	env->str++;
	return (0);
}

int				parse_Osize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 2;
	arg->length = (arg->length < 3) ? 3 : arg->length;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filloct(env, arg);
	env->str++;
	return (0);
}

int				parse_usize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 3;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filluint(env, arg);
	env->str++;
	return (0);
}

int				parse_Usize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 3;
	arg->length = (arg->length < 3) ? 3 : arg->length;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filluint(env, arg);
	env->str++;
	return (0);
}

int				parse_xsize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 4;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillhexa(env, arg);
	env->str++;
	return (0);
}

int				parse_Xsize(t_env *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 5;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillhexa(env, arg);
	env->str++;
	return (0);
}

int				parse_csize(t_env *env, t_arg *arg)
{
	arg->cat = 2;
	arg->type = 6;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	if (buff_fillchar(env, arg) < 0)
		return (-1);
	env->str++;
	return (0);
}

int				parse_Csize(t_env *env, t_arg *arg)
{
	arg->cat = 2;
	arg->type = 6;
	arg->length = (arg->length == 0) ? 3 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	if (buff_fillchar(env, arg) < 0)
		return (-1);
	env->str++;
	return (0);
}

int				parse_ssize(t_env *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 7;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fills(env, arg);
	env->str++;
	return (0);
}

int				parse_Ssize(t_env *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 7;
	arg->length = (arg->length == 0) ? 3 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fills(env, arg);
	env->str++;
	return (0);
}

int				parse_nsize(t_env *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 8;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	return (0);
}

int				parse_psize(t_env *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 9;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	return (0);
}
