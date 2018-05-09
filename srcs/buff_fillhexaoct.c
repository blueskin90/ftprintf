/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillhexaoct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 23:45:26 by toliver           #+#    #+#             */
/*   Updated: 2018/05/04 04:27:45 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			buff_putprefix(t_env *env, char c, int ishash)
{
	if (!ishash)
		return (1);
	else if ((c == 'o' || c == 'O') && ishash) // penser a supprimer ishash
		buff_fillwith(env, '0');
	else if ((c == 'x' || c == 'X') && ishash)
		buff_fillwithstr(env, ((c == 'x') ? "0x" : "0X"));
	else if ((c == 'b' || c == 'B') && ishash)
		buff_fillwithstr(env, ((c == 'b') ? "0b" : "0B"));
	return (1);	
}

int			buff_uimaxtoahexa(t_env *env, uintmax_t value)
{
	uintmax_t		val;
	if (value / 16)
		buff_uimaxtoahexa(env, value / 16);
	val = value % 16;
	if (val < 10)
		buff_fillwith(env, val + '0');
	else
		buff_fillwith(env, val - 10 + ((*env->str == 'x' || *env->str == 'p') ? 'a' : 'A'));
	return (1);
}

int			buff_uimaxtoaoct(t_env *env, uintmax_t value)
{
	if (value / 8)
	{
		buff_uimaxtoaoct(env, value / 8);
		buff_fillwith(env, value % 8 + '0');
	}
	else
		buff_fillwith(env, value + '0');
	return (1);
}

int			buff_filloct(t_env *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	value = get_casteduintmaxt(arg);
	length = ft_uintmaxtlenbase(value, 8);
	length = (value == 0 && arg->prec == 0) ? 0 : length; // nouvel ajout
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	numberofzeroes += (!numberofzeroes && (arg->flags & 2) && (value || !length)) ? 1 : 0; // suppression de & value
	lengthtotal = length + numberofzeroes;
	padding = (arg->width > lengthtotal) ? arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (length > 0) // nouvel ajout
		buff_uimaxtoaoct(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}

int			buff_fillhexa(t_env *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	value = get_casteduintmaxt(arg);
	length = (value == 0 && arg->prec == 0) ? 0 : (int)ft_uintmaxtlenbase(value, 16);
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes + ((arg->flags & 2 && value) ? 2 : 0);
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0 ;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	if (value != 0)
		buff_putprefix(env, *env->str, arg->flags & 2);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (value != 0 || (value == 0 && arg->prec != 0))
		buff_uimaxtoahexa(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}
