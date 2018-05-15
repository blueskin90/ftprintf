/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 08:13:19 by toliver           #+#    #+#             */
/*   Updated: 2018/05/10 14:51:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				tabinit(char tab[], int limit)
{
	int			i;

	i = 0;
	while (i < limit)
	{
		tab[i] = 0;
		i++;
	}
	return (1);
}

int				doubleinit(t_arg *arg, t_splitdouble *final)
{
	t_double	num;
	
	tabinit(final->decivalue, 1074);	
	tabinit(final->intvalue, 310);
	num.val = arg->argument.d;
	final->exp = (num.value.exponent) ? num.value.exponent - 1023 : 0;
	final->exp = (!num.value.exponent && num.value.fraction) ? - 1022 : final->exp;
	final->fraction = num.value.fraction;
	final->fraction += (num.value.exponent && num.value.exponent - 1023 < 1024) ? 0x10000000000000 : 0;
	final->intbit = (num.value.exponent == 0) ? 1 : 0;
	final->bytebufferlimit = 256;
	final->intvaluesize = 310;
	final->decivaluesize = 1074;
	final->finalbuffersize = 1077;
	final->bytepos = 127;
	final->bitpos = 6;
	final->fractionsize = 52;
	final->prec = arg->prec;
	final->iserror = (final->exp == 1024) ? 1 : 0;
	final->isinf = (final->exp == 1024 && final->fraction) ? 0 : 1;
	final->isnan = (final->exp == 1024 && final->fraction) ? 1 : 0;
	final->sign = (!final->isnan) ? num.value.sign : 0;
	final->exponentf = 0;
	final->bitdec = 0;
	final->decistart = 0;
	final->isexponentzero = 0;
	if (final->iserror)
		arg->flags = (arg->flags & 32) ? 32 : 0;
	return (1);
}

int				expset(t_splitdouble *final, t_ldouble num)
{
	if (!num.value.exponent)
	{
		final->iserror = 0;
		final->exp = (!num.value.fraction) ? 0 : -16382;
		final->issub = 1;
	}
	else if (num.value.exponent == 0x7FFF)
	{
		final->iserror = 1;
		final->isinf = (!num.value.fraction) ? 1 : 0;
		final->isnan = (!num.value.fraction) ? 0 : 1;
		if (final->isnan)
			final->sign = 0;
	}
	else
	{
		final->iserror = 0;
		final->exp = num.value.exponent - 16383;
	}
	return (1);
}

int				longdoubleinit(t_arg *arg, t_splitdouble *final, int hexa)
{
	t_ldouble	num;
	
	tabinit(final->decivalue, 16445);	
	tabinit(final->intvalue, 4933);
	num.val = arg->argument.ld;
	if (hexa)
	{
		final->issub = 0;
		if (num.value.exponent)
			num.value.intpart = 1;
	}
	final->sign = num.value.sign;
	final->fraction = num.value.fraction;
	final->intbit = num.value.intpart;
	final->fraction += num.value.intpart * 0x8000000000000000;
	final->bytebufferlimit = 4096;
	final->intvaluesize = 4933;
	final->decivaluesize = 16445;
	final->finalbuffersize = 16448;
	final->bytepos = 2047;
	final->bitpos = 6;
	final->fractionsize = 63;
	final->prec = arg->prec;
	final->exponentf = 0;
	final->decistart = 0;
	final->bitdec = 0;
	final->isexponentzero = 0;
	expset(final, num);
	if (final->iserror && (arg->flags & 8))
		arg->flags ^= 8;
	return (1);
}

/*
int					splitinit(t_arg *arg, t_splitdouble *num, int hexa)
{
	if (arg->length == 8)
		longdoubleinit(arg, num, hexa);
	else
		doubleinit(arg, num);
	return (1);
}
*/

int					splitinit(t_arg *arg, t_splitdouble *num)
{
	if (arg->length == 8)
		longdoubleinit(arg, num);
	else
		doubleinit(arg, num);
	return (1);
}

