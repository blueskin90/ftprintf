/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_filldeci.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 02:23:40 by toliver           #+#    #+#             */
/*   Updated: 2018/06/01 09:46:24 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				fillint(t_bigint *number, t_splitd *num)
{
	int			i;
	int			bitread;
	int			bitsize;

	bitsize = (num->islong) ? 63 : 52;
	i = num->exp;
	while (i > bitsize)
	{
		multab(number, 2);
		i--;
	}
	bitread = 0;
	while (i >= 0)
	{
		if (num->fra & (1ull << (bitsize - i)))
			addtab(number);
		bitread++;
		multab(number, 2);
		i--;
	}
	return (1);
}	

int				filldeci(t_bigint *number, t_splitd *num)
{
	int			i;
	int			bitread;
	int			bitsize;
	
	bitsize = (num->islong) ? 63 : 52;
	i = num->exp;
	number->number[967] = 1;
	if (num->exp < -1)
	{
		while (i < -1)
		{
			mulnum(number, 10);
			multab(number, 5);
			i++;
		}
	}
	bitread = 1 + i;
	while (i <= bitsize) 
	{
		mulnum(number, 10);
		if ((num->fra >> (bitsize - bitread)) & 1ull)
			addtab(number);
		bitread++;
		multab(number, 5);
		i++;
	}
	return (1);
}	

int				initbigint(t_bigint *number)
{
	int						i;
	i = 0;
	number->rank = 0;
	i = 0;
	while (i < 968)
	{
		number->value[i] = 0;
		number->number[i] = 0;
		i++;
	}
	i = 0;
	while (i < 16457)
	{
		number->fullnum[i] = 0;
		i++;
	}
	number->fullnumbuffer = 0;
	return (1);
}

int			resetbigint(t_bigint *number)
{
	int						i;
	i = 0;
	number->rank = 0;
	while (i < 968)
	{
		number->value[i] = 0;
		number->number[i] = 0;
		i++;
	}
	return (1);
}

int				write_bigint(t_bigint *number)
{
	int			value;

	if (!(number->rank == -1))
	{
		value = divtab(number, 10) + '0';
		write_bigint(number);
		number->fullnum[number->fullnumbuffer] = (char)value;
		number->fullnumbuffer++;
	}
	return (1);
}

int				copyintvalue(t_bigint *number)
{
	write_bigint(number);
	if (number->fullnumbuffer == 0)
	{
		number->fullnum[0] = '0';
		number->fullnumbuffer++;
	}
	return (1);
}

int				copydecivalue(t_bigint *number)
{
	int			i;
	int			ii;

	write_bigint(number);
	i = number->comapos + 1;
	ii = number->comapos + 2;
	while (ii < 16457 && number->fullnum[ii])
	{
		number->fullnum[i] = number->fullnum[ii];
		i++;
		ii++;
	}
	number->fullnumbuffer--;
	while (number->fullnum[number->fullnumbuffer - 1] == '0')
		number->fullnumbuffer--;
	return (1);
}
/*
int				fillzeroes(t_bigint *number, t_splitd *num)
{
	int			numberofzeroes;

	numberofzeroes = -num->exp + ((num->islong) ? 63 : 52);
	if (numberofzeroes > 0 && numberofzeroes > number->fullnumbuffer - number->comapos)
	{
		ii = number->comapos + numberofzeroes;
		i = number->fullnumbuffer - 1;
		number->fullnumbuffer = ii + 1;
		while (i > number->comapos)
		{
			number->fullnum[ii] = number->fullnum[i];
			i--;
			ii--;
		}
		while (ii > number->comapos)
		{
			number->fullnum[ii] = '0';
			ii--;
		}
	}
	return (1);
}
*/

int				mustround(t_bigint *number, int prec, int numberofdeci)
{
	int			i;

	i = number->comapos + prec + 2;
	while (i < (numberofdeci + number->comapos) && number->fullnum[i] == '0')
		i++;
	if (i < numberofdeci + number->comapos)
		return (1);
	i = number->comapos + prec;
	if ((prec != 0 && number->fullnum[i] % 2 == 1) || (prec == 0 && number->fullnum[number->comapos - 1] % 2 == 1))
		return (1);
	return (0);
}

int				float_rounding(t_bigint *number, int *prec)
{
	int			numberofdeci;
	int			i;
	int			retenue;

	numberofdeci = number->fullnumbuffer - 1 - number->comapos;
	retenue = 0; // a supprimr quand jaurai remplace le else if par els
	if (*prec < 0)
		*prec = 6;
//	printf("\n==num = %c numberofdeci = %d, preci = %d comapos = %d==\n", number->fullnum[number->comapos + *prec + 1], numberofdeci, *prec, number->comapos);
	if ((*prec) + 1 > numberofdeci || number->fullnum[number->comapos + *prec + 1] < '5')
		return (1);
	else if(number->fullnum[number->comapos + *prec + 1] > '5')
		retenue = 1;
	else if (number->fullnum[number->comapos + *prec + 1] == '5' && mustround(number, *prec, numberofdeci))
			retenue = 1;
	i = number->comapos + *prec;
	while (retenue != 0 && i != number->comapos)
	{
		number->fullnum[i] += retenue;
		retenue = (number->fullnum[i] <= '9') ? 0 : 1;
		number->fullnum[i] = (retenue) ? number->fullnum[i] - 10 : number->fullnum[i];
		i--;
	}
	if (retenue == 1 && i == number->comapos)
	{
		i--;
		while (i >= 0 && retenue)
		{
			number->fullnum[i] += retenue;
			retenue = (number->fullnum[i] <= '9') ? 0 : 1;
			number->fullnum[i] = (retenue) ? number->fullnum[i] - 10 : number->fullnum[i];
			i--;
		}
		if (i < 0 && retenue)
		{
			i = number->fullnumbuffer - 1;
			while (i >= 0)
			{
				number->fullnum[i + 1] = number->fullnum[i];
				i++;
			}
			number->fullnum[0] = retenue + '0';
			number->comapos++;
			number->fullnumbuffer++;
		}
	}
	return (1);
}

int				putfloatsign(int sign, char flags, t_env *env)
{
	if (sign)
		buff_fillwith(env, '-');
	else if (!sign && (flags & 4))
		buff_fillwith(env, ' ');
	else if (!sign && (flags & 16))
		buff_fillwith(env, '+');
	return (1);
}

int				float_writeoutput(t_bigint *number, t_splitd *num, t_env *env, t_arg *arg)
{
	int			charnumber;
	int			padding;
	int			i;

	charnumber = number->comapos;
	if (!(arg->prec == 0 && !(arg->flags & 2)))
		charnumber += 1;
	charnumber += arg->prec;
	charnumber += ((num->sign || (arg->flags & 16) || (arg->flags & 4)) ? 1 : 0);
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
	if (padding)
		buff_fillwithnumber(env, ' ', padding);
	return (1);
}

int				fill_bigint(t_bigint *number, t_splitd *num)
{
	int						testvalue;
	
	initbigint(number);
	number->value[967] = 1;
	fillint(number, num);
	copyintvalue(number);
	resetbigint(number);
	number->value[967] = 5;
	filldeci(number, num);
	number->comapos = number->fullnumbuffer;
	number->fullnum[number->fullnumbuffer] = '.';
	number->fullnumbuffer++;
	testvalue = number->fullnumbuffer;
	copydecivalue(number);
	return (1);
}

int				buff_fillfloatdeci(t_splitd *num, t_bigint *number, t_env *env, t_arg *arg)
{

	fill_bigint(number, num);	
	float_rounding(number, &(arg->prec));
	float_writeoutput(number, num, env, arg);
	return (1);
}
