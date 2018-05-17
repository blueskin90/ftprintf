/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:26:29 by toliver           #+#    #+#             */
/*   Updated: 2018/05/17 02:53:38 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_string(t_env *env)
{
	int			retval;

	while (*env->str)
	{
		if (*env->str == '%')
		{
			env->str++;
			if (*env->str)
			{
				if ((retval = parse_token(env)) == -1)
					return (-1);
				else
					env->buffilasttoken = env->buffi;
			}
		}
		else
		{
			buff_fillwith(env, *env->str);
			env->str++;
		}
	}
	env->buffilasttoken = env->buffi;
	return (1);
}

int				parse_token(t_env *env)
{
	t_arg		arg;
	int			retval;

	arg_init(&arg);
	while ((retval = env->parse[(int)*env->str](env, &arg)) > 0)
		;
// remplacer par ALL apres
//		env->parse[*env->str + 128]; a faire quand jaurai fini mon array
//	printf("param = %d\nflags = %hhd\nwidth = %d\nprec = %d\nlength = %hhd\n type = %hhd\n", arg.param, arg.flags, arg.width, arg.prec, arg.length, arg.type); // a delete apres, pour verifier que mon token est correct
//	printf("%s\n", env->str);    // a decomenter si ca bug
	return (retval);
}

void			arg_init(t_arg *arg)
{
	arg->param = 0;
	arg->flags = 0;
	arg->width = -1;
	arg->prec = -1;
	arg->length = 0;
	arg->type = -1;
	arg->cat = 0;
	arg->argument.i = 0;
}

int					pfatoi(t_env *env)
{
	long long int	result;

	result = 0;
	while (*env->str >= '0' && *env->str <= '9')
	{
		result = result * 10 + *env->str - '0';
		env->str++;
		if (result > 2147483647)
		{
			while (*env->str >= '0' && *env->str <= '9')
				env->str++;
			return (-1);
		}
	}
	return ((int)result);
}

int				parse_error(t_env *env, t_arg *arg)
{
	if (*env->str)
	{
		arg->argument.uc = *env->str;
		arg->cat = 2;
		flags_cleanup(arg);
		if (buff_fillchar(env, arg) < 0)
			return (-1);
		env->str++;
	}
	return (0);
}

int				parse_preci(t_env *env, t_arg *arg) // penser au wildchar
{
	env->str++;
	if (*env->str == '*')
	{
		arg->prec = va_arg(env->arg, int);
		if (arg->prec < 0) 
			arg->prec = -1;
		env->str++;
	}
	else
	{
		arg->prec = pfatoi(env);
		if (arg->prec < 0)
			arg->prec = -1;
	}
	return (1);
}

int				parse_wildchar(t_env *env, t_arg *arg)
{
	int			value;

	value = va_arg(env->arg, int);
	env->str++;
	if (*env->str == '$')
	{
		arg->param = value;
		env->str++;
	}
	else
	{
		arg->width = value;
		if (arg->width < 0) 
		{
			arg->width = (-arg->width);
			arg->flags |= 32;
		}
	}
	return (1);
}

int				parse_number(t_env *env, t_arg *arg)
{
	int			value;

	value = pfatoi(env);
	if (*env->str == '$')
	{
		arg->param = value;
		env->str++;
	}
	else
		arg->width = value;
	return (1);
}
