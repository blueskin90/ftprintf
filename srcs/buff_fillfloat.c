/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:52:38 by toliver           #+#    #+#             */
/*   Updated: 2018/06/01 10:28:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					initdouble(t_splitd *num, double val)
{
	t_double		split;

	split.val = val;
	num->sign = split.value.sign;
	num->islong = 0;
	num->isnan = 0;
	num->isinf = 0;
	num->iszero = 0;
	if (split.value.exp == DBL_MAX_EXP_VAL)
	{
		num->isinf = ((split.value.fra) ? 0 : 1);
		num->isnan = !num->isinf;
	}
	else if (split.value.exp == 0)
	{
		num->issub = ((split.value.fra) ? 1 : 0);
		num->exp = (num->issub) ? -1022 : 0;
		num->fra = (num->issub) ? split.value.fra : 0;
		num->iszero = !num->issub;
	}
	else
	{
		num->exp = split.value.exp - 1023;
		num->fra = split.value.fra + 0x10000000000000;
	}
	return (1);
}

int					initlongdouble(t_splitd *num, long double val)
{
	t_ldouble		split;

	split.val = val;
	num->sign = split.value.sign;
	num->islong = 1;
	num->isnan = 0;
	num->isinf = 0;
	num->iszero = 0;
	num->issub = 0;
	if (split.value.exp == 0)
	{
		if (!split.value.fra)
			num->iszero = 1;
		else
		{
			num->exp = -16382;
			num->fra = split.value.fra + 0x8000000000000000 * split.value.intpart;
			num->issub = 1;
		}
	}
	else if (split.value.exp == LDBL_MAX_EXP_VAL)
	{
		num->isnan = (split.value.fra) ? 1 : 0;
		num->isinf = !num->isnan;
	}
	else
	{
		num->exp = split.value.exp - 16383;
		num->fra = split.value.fra + 0x8000000000000000 * split.value.intpart;
	}
	return (1);
}

int				splitinit(t_arg *arg, t_splitd *num, t_env *env)
{
	if (!(arg->length == 8))
		initdouble(num, arg->argument.d);
	else
		initlongdouble(num, arg->argument.ld);
	num->isrounded = 0;
	num->isuppercase = (*env->str <= 'Z') ? 1 : 0;
	num->type = (*env->str == 'f' || *env->str == 'F') ? ISDECI : num->type;
	num->type = (*env->str == 'e' || *env->str == 'E') ? ISEXP : num->type;
	num->type = (*env->str == 'g' || *env->str == 'G') ? ISSHORTEST : num->type;
	num->type = (*env->str == 'a' || *env->str == 'A') ? ISHEXA : num->type;
	if (num->type == ISHEXA && num->islong && !num->issub)
		num->fra |= 0x8000000000000000;
	return (1);
}
/*
int						roundinghexa(t_splitd *num, char value[])
{
	int					i;
	int					test[16];
	int					retenue;

	i = 0;
	(void)num;
//	while (i < 16)
//	{
//		printf("%c", value[i] + ((value[i] <= 9) ? '0' : 'a' - 10));
//		i++;
//	}
//	printf("\n");

	i = 15;
	while (i > num->prec)
	{
		test[i] = (value[i] >> 1) + ((i > 0 && i < num->prec - 1) ? ((value[i] & 0b1) << 3) : 0);
		i--;
	}
	while (i > 0)
	{
		test[i] = 0;
		i--;
	}
	i = 0;
//	while (i < 16)
//	{
//		printf("%c", test[i] + ((test[i] <= 9) ? '0' : 'a' - 10));
//		i++;
//	}
//	printf("\n");
	i = 15;
	retenue = 0;
	while (i >= 0)
	{
		value[i] += test[i] + retenue;
		retenue = value[i] / 16;
		value[i] %= 16;
		i--;
	}
	if (i == 0 && retenue)
		num->isrounded = 1;
	return (1);
}
*/
int						roundinghexa(t_splitd *num, char value[])
{
	int					i;
	
	if (value[num->prec + 1] < 8)
		return (0);
	else if (value[num->prec + 1] > 8)
		value[num->prec] += 1;

	else if (value[num->prec + 1] == 8)// && (value[num->prec] & 1)) //&& value[num->prec] % 2 != 0)
	{
		i = 0;
		while (num->prec + 1 + i < 16 && value[num->prec + 1 + i] == 0)
			i++;
		if ((num->prec + 1 + i == 16 && !(value[num->prec] & 1)) || num->prec + 1 + i < 16)
			value[num->prec] += 1;
	}
	i = num->prec;
	while (value[i] > 15 && i >= 0)
	{
		if (i > 0)
			value[i - 1] += 1;
		else
		{
			num->exp -= 4; // ptet a changer si ca merde
			num->isrounded = 1;
			num->decisize--;
		}
		value[i] -= 16;
		i--;
	}
	return (1);
}

int						hexavaluesetd(t_hexa hex, t_splitd *num, char value[])
{
	int					i;
	int					ii;

	i = 7;
	ii = 0;
	while (((hex.byte[7] & 0xf0)) < 1)
	{
		hex.fra = hex.fra << 1;
		num->exp--;
	}
	while (i >= 0)
	{
		value[ii] = ((hex.byte[i] & 0xf0) >> 4);
		value[ii + 1] = hex.byte[i] & 0xf;
		ii += 2;
		i--;
	}
	return (1);
}

int						setaswritable(char value[], int size, int uppercase)
{
	int		i;

	i = 0;
	while (i < size)
	{
		value[i] += (value[i] <= 9) ? '0' : 'a' - 10 - 32 * uppercase;
		i++;
	}
	return (1);
}

int						numberlen(int number)
{
	int		i;

	i = 1;
	number = (number < 0) ? -number : number;
	while (number / 10)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

int						buff_fillexponenthexa(t_env *env, int up, int exp)
{
	buff_fillwith(env, ((up) ? 'P' : 'p'));
	buff_fillwith(env, ((exp >= 0) ? '+' : '-'));
	buff_imaxtoa(env, exp);
	return (1);
}

int						writehexa(t_splitd *num, t_env *env, char value[], t_arg *arg)
{
	int					length;
	int					padding;
	int					i;


	length = num->intsize + ((num->prec == -1) ? num->decisize : num->prec) + (((num->prec != 0) || arg->flags & 2) ? 1 : 0) + 4 + numberlen(num->exp) + (((arg->flags & 16) || (arg->flags & 4) || num->sign) ? 1 : 0);
	padding = (arg->width - length > 0) ? arg->width - length : 0;
	if (padding && !(arg->flags & 32) && !(arg->flags & 8))
		buff_fillwithnumber(env, ' ', padding);
	if (num->sign)
		buff_fillwith(env, '-');
	else if ((arg->flags & 16) || (arg->flags & 4))
		buff_fillwith(env, ((arg->flags & 16) ? '+' : ' '));
	buff_fillwithstr(env, ((num->isuppercase) ? "0X" : "0x"));
	if (padding && (arg->flags & 8))
		buff_fillwithnumber(env, '0', padding);
	buff_fillwith(env, ((num->isrounded) ? '1' : value[0]));
	if (((num->prec == -1) && num->decisize) || arg->flags & 2 || num->prec > 0)
		buff_fillwith(env, '.');
	if (num->prec > 0 || num->prec == -1)
	{
		i = (num->isrounded) ? 0 : 1;
		while (i <= num->decisize)
		{
			buff_fillwith(env, value[i]);
			i++;
		}
	}
	if (arg->prec > num->decisize)
		buff_fillwithnumber(env, '0', arg->prec - num->decisize);
	buff_fillexponenthexa(env, num->isuppercase, num->exp);
	if (padding && (arg->flags & 32) && !(arg->flags & 8))
		buff_fillwithnumber(env, ' ', padding);
//	printf("length = %d, intsize = %d, decisize = %d, numberlen = %d, num->exp %d\n", length, num->intsize, num->decisize, numberlen(num->exp), num->exp);
	// affichage de test
	
//	write(1, value, 16);
//	printf("%+d\n", num->exp);// penser apres a le faire varier selon les arrondis
	(void)env;
	return (1);
}

int						buff_fillhexalongd(t_splitd *num, t_env *env, t_arg *arg)
{
	t_hexa				hex;
	char				value[16];

	if (!num->iszero)
	{
		hex.fra = num->fra;
		hexavaluesetd(hex, num, value);	
	}
	num->intsize = 1;
	num->decisize = (num->iszero) ? 0 : 15;
	num->prec = (num->iszero) ? 0 : num->prec;
	while (value[num->decisize] == 0 && num->decisize > 0)
		num->decisize--;
	if (num->prec != -1 && num->prec < num->decisize && !num->iszero)
	{
		roundinghexa(num, value);
		num->decisize = num->prec;
	}
	if (!num->iszero)
		setaswritable(value, 16, num->isuppercase);
	writehexa(num, env, value, arg);

	//printf("num->decisize = %d\n", num->decisize);// nombre de decimaux, coincide avec la position dans le tableau de chars :D
	return (1);
}

int						buff_fillhexad(t_splitd *num, t_env *env, t_arg *arg)
{
	t_hexa				hex;
	char				value[16];

	if (!num->iszero)
	{
		hex.fra = num->fra << 8;
		hexavaluesetd(hex, num, value);	
	}
	num->intsize = 1;
	num->decisize = (num->iszero) ? 0 : 15;
	num->prec = (num->iszero) ? 0 : num->prec;
	while (value[num->decisize] == 0 && num->decisize > 0)
		num->decisize--;
	if (num->prec != -1 && num->prec < num->decisize && !num->iszero)
	{
		roundinghexa(num, value);
		num->decisize = num->prec;
	}
	setaswritable(value, 16, num->isuppercase);
	writehexa(num, env, value, arg);

	//printf("num->decisize = %d\n", num->decisize);// nombre de decimaux, coincide avec la position dans le tableau de chars :D
	return (1);
}
// avec 0 ca affiche du caca :(
int						buff_fillerror(t_splitd *num, t_env *env, t_arg *arg)
{
	char				buffer[5];
	int					i;

	i = 0;
	if (num->isinf)
	{
		if (num->sign)
			buffer[i++] = '-';
		else if ((arg->flags & 16) || (arg->flags & 4))
			buffer[i++] = ((arg->flags & 16) ? '+' : ' ');
		buffer[i++] = (num->isuppercase) ? 'I' : 'i';
		buffer[i++] = (num->isuppercase) ? 'N' : 'n';
		buffer[i++] = (num->isuppercase) ? 'F' : 'f';
	}
	else
	{
		buffer[i++] = (num->isuppercase) ? 'N' : 'n';
		buffer[i++] = (num->isuppercase) ? 'A' : 'a';
		buffer[i++] = (num->isuppercase) ? 'N' : 'n';
	}
	buffer[i] = 0;
	arg->length = 0;
	arg->flags &= 32;
	arg->prec = i;
	arg->argument.cptr = (char*)(&buffer);
	buff_fills(env, arg);
	return (1);
}

int						buff_fillfloat(t_env *env, t_arg *arg)
{
	static t_splitd		num;
	static t_bigint		number;

	splitinit(arg, &num, env);
	num.prec = arg->prec;
	num.width = arg->width;
	if (num.isinf || num.isnan)
		buff_fillerror(&num, env, arg);
	else if (num.type == ISHEXA)
		(num.islong) ? buff_fillhexalongd(&num, env, arg) : buff_fillhexad(&num, env, arg);
	else if (num.type == ISEXP)
		buff_fillexp(&num, &number, env, arg);
	else if (num.type == ISDECI)
		buff_fillfloatdeci(&num, &number, env, arg);
	return (1);
}
