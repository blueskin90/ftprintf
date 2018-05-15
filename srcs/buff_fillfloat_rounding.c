/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_rounding.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 09:53:48 by toliver           #+#    #+#             */
/*   Updated: 2018/05/10 13:33:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					mustround(char value[], int limit, int start)
{
	int				i;

	i = start;
	while (!value[i] && i < limit)
		i++;
	if (value[i] > '5' || (value[i - 1] == '5' && i == limit))
		return (1);
	else if (i == limit || value[i] < '5')
		return (0);
	i++;
	while (i < limit && value[i] == '0')
		i++;
	if (i == limit)
		return (0);
	return (1);
}

int					roundingint(char value[], int limit)
{
	int				i;

	i = limit - 1;
	value[i] += 1;
	while (value[i] > '9' && i >= 0)
	{
		value[i] -= 10;
		if (i != 0)
			value[i - 1] += 1;
		i++;
	}
	return (1);
}
int					roundingdeci(char value[], int limit, t_splitdouble *num, int prec)
{
	int				i;

	i = limit - num->fractionsize + num->exp + prec - 1;
	if (i < limit)
	{
		if (i == limit - 1 && value[i] >= '5')
		{
			if (value[i] > 5)
			{
				value[i - 1] += 1;
				i--;
			}
			else if (value[i] == 5)
			{
				value[i - 1] += ((value[i - 1] & 1) ? 1 : 0);
			}
		}
		else if (i < limit - 1)
		{
			if (value[i + 1] > '5')
			{
				value[i] += 1;
			}
			else if (value[i + 1] == '5')// && mustround(value, limit, i + 1))
				value[i] += (value[i] & 1) ? 1 : 0;
		}
		while (value[i] > '9' && i > 0 && value[i - 1])
		{
			value[i] -= 10;
			value[i - 1] += 1;
			i--;
		}
		if ((i == 0 && value[i] > '9') || (i != 0 && !value[i - 1] && value[i] > '9'))
		{
			value[i] -= 10;
			return (1);
		}
		else if (i == 0 && value[i] == '5')
			return ((num->intvalue[0] & 1) ? 1 : 0);
	}
	return (0);
}

int					roundingintexp(char value[], int limit, t_splitdouble *num)
{
	value[limit - 1] += 1;
	if (value[limit - 1] > '9')
	{
		value[limit - 1] = '1';
		num->exponentf += (num->sign == 1) ? -1 : 1;
	}
	return (1);
}

int					roundingdeciexp(char value[], int limit, t_splitdouble *num, int prec)
{
//probleme arrondi sur certaines valeurs de merd
	int				i;

	if (num->exponentf >= 0)	
		i = num->decistart + prec - 1;
	else
	{
		i = num->decivaluesize + num->exp - num->fractionsize + prec - 1;
		num->decistart = num->decivaluesize + num->exp - num->fractionsize;
	}
// le i tombe pas sur la bonne case pour arrondir
//	while (i < num->decivaluesize)
//	{
//		printf("%c", value[i]);
//		i++;
//	}
//	printf("\n");
//	i = num->decistart + prec - 1;
	if (i < limit)
	{
		if (i == limit - 1 && value[i] >= '5')
		{
			value[i - 1] += 1;
			i--;
		}
		else if (i < limit - 1)
		{
			if (value[i + 1] > '5')
				value[i] += 1;
			else if (value[i + 1] == '5' && mustround(value, limit, i + 1))
				value[i] += 1;
		}
		while (value[i] > '9' && i > num->decistart && value[i - 1])
		{
			value[i] -= 10;
			value[i - 1] += 1;
			i--;
		}
		if ((i == num->decistart && value[i] > '9') || (!value[i - 1] && value[i] > '9'))
		{
			value[i] -= 10;
			return (1);
		}
	}
	return (0);
}

int					roundingnumberexp(t_splitdouble *num, int prec)
{
	if (prec == 0 && mustround(num->decivalue, num->decivaluesize, num->decistart))
		roundingintexp(num->intvalue, num->intvaluesize, num);
	else if (prec > 0 && prec < num->bitdec && num->bitdec)
		if (roundingdeciexp(num->decivalue, num->decivaluesize, num, prec) == 1)
			roundingintexp(num->intvalue, num->intvaluesize, num);
	return (1);
}

int					roundingnumber(t_splitdouble *num, int prec)
{
	if (prec == 0 && mustround(num->decivalue, num->decivaluesize, 0))
		roundingint(num->intvalue, num->intvaluesize);
	else if (prec > 0 && prec < num->bitdec && num->bitdec)
		if (roundingdeci(num->decivalue, num->decivaluesize, num, prec) == 1)
			roundingint(num->intvalue, num->intvaluesize);
	return (1);
}
