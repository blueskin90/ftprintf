/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 03:27:05 by toliver           #+#    #+#             */
/*   Updated: 2018/04/13 03:19:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		ft_wstrlen(wint_t *str)
{
	int		i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

size_t		ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t		chartofill(t_arg *arg, int wchar)
{
	size_t	strlen;

	if (!wchar)
	{
			strlen = ft_strlen(arg->argument.cptr);
		if (arg->prec >= 0 && (size_t)arg->prec < strlen) //valeurs negatives ?
			strlen = arg->prec;
		if (arg->width >= 0 && (size_t)arg->width > strlen)
			return (arg->width - strlen);
	}
	return (0);
}

int			buff_fills(t_env *env, t_arg *arg)
{
	int		i;

	i = -1;
	if (ARG.cptr == NULL)
		ARG.cptr = env->null;
	if (arg->length != 0)
		return (buff_fillwstr(env, arg));
	if (!(arg->flags & 32) && chartofill(arg, 0))
		buff_padding(env, arg, chartofill(arg, 0));
	while (arg->argument.cptr[++i] && ((arg->prec == -1) || i < arg->prec))
		buff_fillwith(env, ARG.cptr[i]);
	if ((arg->flags & 32) && chartofill(arg, 0))
		buff_padding(env, arg, chartofill(arg, 0));
	return (1);	
}

size_t		ft_wcharstrlen(t_env *env, t_arg *arg)
{
	size_t	i;
	size_t	charnbr;
	int		bytenumber;
	(void)env;
	i = 0;
	charnbr = 0;
	while (ARG.wcptr[i])
	{
		bytenumber = octsize(ARG.wcptr[i]);
		if (arg->prec >= 0 && ((int)charnbr + bytenumber) > arg->prec)
			break;
		if (bytenumber > 0)
			charnbr += bytenumber;
		else if (bytenumber == 0 && ARG.wcptr[i] <= 0xff && MB_CUR_MAX == 1)
			charnbr += 1;
		i++;
	}
	if (arg->prec > 0)
		arg->prec = -1;
	arg->width -= charnbr; // le nombre de 0 ou espaces a mettre
	return (i);	
}

int			buff_fillwstr(t_env *env, t_arg *arg)
{
	size_t	i;
	size_t	charnbr;
	wint_t	wch;

	if (ARG.wcptr == NULL)
	{
		arg->length = 0;
		return(buff_fills(env, arg));
	}
	i = -1;
	charnbr = ft_wcharstrlen(env, arg);
	if (!(arg->flags & 32) && arg->width > 0)
		buff_padding(env, arg, arg->width);
	while (ARG.wcptr[++i] && arg->prec < 0 && i < charnbr)
	{
		wch = ARG.wcptr[i];
		if (wch >= 0xD800 && wch <= 0xDFFF)
			return (-1);
		else if (wch <= 127 || (wch <= 0xff && MB_CUR_MAX == 1))
			buff_fillwith(env, wch);
		else
			buff_putwchar(env, ARG.wcptr[i]);
	//	printf("%d wch char du buffer = %c \n", (signed char)wch, env->buff[env->buffi - 1]);
	}
	if ((arg->flags & 32) && arg->width > 0)
		buff_padding(env, arg, arg->width);
	return (1);	
}

intmax_t	get_castedintmaxt(t_arg *arg) // faire un tableau de fonctions
{
	if (arg->length == 0)
		return ((intmax_t)ARG.i);
	else if (arg->length == 1)
		return ((intmax_t)ARG.sc);
	else if (arg->length == 2)
		return ((intmax_t)ARG.si);
	else if (arg->length == 3)
		return ((intmax_t)ARG.li);
	else if (arg->length == 4)
		return ((intmax_t)ARG.lli);
	else if (arg->length == 5)
		return ((intmax_t)ARG.imax);
	else if (arg->length == 6)
		return ((intmax_t)ARG.siz);
	else if (arg->length == 7)
		return ((intmax_t)ARG.ptd);
	else
		return ((intmax_t)ARG.i);
}

intmax_t	get_casteduintmaxt(t_arg *arg) // faire un tableau de fonctions
{
	if (arg->length == 0)
		return ((intmax_t)ARG.ui);
	else if (arg->length == 1)
		return ((intmax_t)ARG.uc);
	else if (arg->length == 2)
		return ((intmax_t)ARG.usi);
	else if (arg->length == 3)
		return ((intmax_t)ARG.uli);
	else if (arg->length == 4)
		return ((intmax_t)ARG.ulli);
	else if (arg->length == 5)
		return ((intmax_t)ARG.uimax);
	else if (arg->length == 6)
		return ((intmax_t)ARG.siz);
	else if (arg->length == 7)
		return ((intmax_t)ARG.ptd);
	else
		return ((intmax_t)ARG.i);
}

size_t		ft_uintmaxtlenbase(uintmax_t value, int base)
{
	size_t	i;

	i = 1;
	while (value / base > 0)
	{
		value = value / base;
		i++;
	}
	return (i);
}

size_t		ft_intmaxtlenbase(intmax_t value, int base)
{
	if (value < 0)
		return (ft_uintmaxtlenbase((uintmax_t)-value, base));
	else
		return (ft_uintmaxtlenbase((uintmax_t)value, base));
}

int			buff_putsign(t_env *env, intmax_t value, int plus, int space)
{	
	if (value < 0)
		buff_fillwith(env, '-');
	else if (plus)
		buff_fillwith(env, '+');
	else if (space)
		buff_fillwith(env, ' ');
	return (1);
}

int			buff_imaxtoa(t_env *env, intmax_t value)
{
	if (value < 0)
		return (buff_uimaxtoa(env, -value));
	else
		return (buff_uimaxtoa(env, value));
}

int			buff_uimaxtoa(t_env *env, uintmax_t value)
{
	if (value >= 10)
	{
		buff_uimaxtoa(env, value / 10);
		buff_fillwith(env, value % 10 + '0');
	}
	else
		buff_fillwith(env, value + '0');
	return (1);
}



int			buff_fillint(t_env *env, t_arg *arg)
{
	intmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	value = get_castedintmaxt(arg);
	length = (value == 0 && arg->prec == 0) ? 0 : (int)ft_intmaxtlenbase(value, 10);
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes + 
		(((arg->flags & 16) || (arg->flags & 4) || value < 0) ? 1 : 0);
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0 ;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	buff_putsign(env, value, arg->flags & 16, arg->flags & 4);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (value != 0 || (value == 0 && arg->prec != 0))
		buff_imaxtoa(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}

int			buff_filluint(t_env *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	value = get_casteduintmaxt(arg);
	length = (value == 0 && arg->prec == 0) ? 0 : (int)ft_uintmaxtlenbase(value, 10);
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes; 
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0 ;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (value != 0 || (value == 0 && arg->prec != 0))
		buff_uimaxtoa(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}
