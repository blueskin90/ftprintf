/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_exp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 06:15:36 by toliver           #+#    #+#             */
/*   Updated: 2018/06/01 10:14:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				sizeofexponent(int exp)
{
	int			len;

	len = ft_intmaxtlenbase(exp, 10);
	len = ((len < 2) ? 2 : len);
	len += 2;
	return (len);
}

int				putexponent(int exp, int isuppercase, t_env *env)
{
	buff_fillwith(env, ((isuppercase) ? 'E' : 'e'));
	buff_fillwith(env, ((exp < 0) ? '-' : '+'));
	if (ft_intmaxtlenbase(exp, 10) < 2)
		buff_fillwith(env, '0');
	buff_imaxtoa(env, (intmax_t)exp);
	return (1);
}

int				float_writeexpoutput(t_bigint *number, t_splitd *num, t_env *env, t_arg *arg)
{
	int			charnumber;
	int			padding;
	int			i;

	charnumber = number->comapos;
	if (!(arg->prec == 0 && !(arg->flags & 2)))
		charnumber += 1;
	charnumber += arg->prec;
	charnumber += ((num->sign || (arg->flags & 16) || (arg->flags & 4)) ? 1 : 0);
	charnumber += sizeofexponent(number->exp);
	padding = ((arg->width > charnumber) ? arg->width - charnumber : 0);
	if (padding && !(arg->flags & 32) && !(arg->flags & 8))
	{
		buff_fillwithnumber(env, ' ', padding);
		padding = 0;
	}
	putfloatsign(num->sign, arg->flags, env);
	if (padding && (arg->flags & 8))
	{
		buff_fillwithnumber(env, '0', padding);
		padding = 0;
	}
	i = 0;
	while (i < number->comapos)
	{
		buff_fillwith(env, number->fullnum[i]);
		i++;
	}
	if (!(arg->prec == 0 && !(arg->flags & 2)))
	{
		buff_fillwith(env, '.');
		i++;
	}
	while (arg->prec > 0 && i < number->fullnumbuffer && number->fullnum[i])
	{
		buff_fillwith(env, number->fullnum[i]);
		i++;
		arg->prec--;
	}
	while (arg->prec > 0)
	{
		buff_fillwith(env, '0');
		arg->prec--;
	}
	putexponent(number->exp, num->isuppercase, env);
	if (padding)
		buff_fillwithnumber(env, ' ', padding);
	return (1);
}

int				exp_setting(t_bigint *number)
{
	int			i;

	number->exp = 0;
	while (number->fullnum[1] != '.')
	{
		number->fullnum[number->comapos] = number->fullnum[number->comapos - 1];
		number->fullnum[number->comapos - 1] = '.';
		number->comapos--;
		number->exp++;	
	}
	while (number->fullnum[0] == '0')
	{
		number->fullnum[0] = number->fullnum[2];
		i = 2;
		while (i < number->fullnumbuffer && i < 16455)
		{
			number->fullnum[i] = number->fullnum[i + 1];
			i++;
		}
		number->fullnumbuffer--;
		number->exp--;
	}
	return (1);
}

int				buff_fillexp(t_splitd *num, t_bigint *number, t_env *env, t_arg *arg)
{
	fill_bigint(number, num);
	exp_setting(number);
	float_rounding(number, &(arg->prec));
	if (number->comapos != 1)
	{
		number->fullnum[2] = number->fullnum[1];
		number->fullnum[1] = '.';
		number->exp++;
	}
//	write(1, number->fullnum, 16457);
//printf("p%+2d\n", exp);
	float_writeexpoutput(number, num, env, arg);
	return (1);
}
