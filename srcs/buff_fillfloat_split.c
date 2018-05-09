/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 09:50:17 by toliver           #+#    #+#             */
/*   Updated: 2018/05/09 12:27:22 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				setcharvalue(t_splitdouble *num)
{
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (i < num->decivaluesize)
	{
		num->decivalue[i] += '0';
//		write(1, num->decivalue + i, 1);
		i++;
	}
	i = 0;
//	write(1, "\n", 1);
	while (i < num->intvaluesize)
	{
		if (num->intvalue[i] != 0)
			check = 1;
		if (check == 1)
		{
			num->intvalue[i] += '0';
	//		write(1, num->intvalue + i, 1);
		}
		i++;
	}
//	printf("\nnum->exponentf %d\n", num->exponentf);
	return (1);
}

int				decistartset(t_splitdouble *num)
{
	int			i;
	int			j;

	i = num->decivaluesize - num->fractionsize + num->exp;
	num->exponentf = -1;
	while (i < num->decivaluesize && num->decivalue[i] == 0)
	{
		num->exponentf--;
		i++;
	}
	num->intvalue[num->intvaluesize - 1] = num->decivalue[i];
	i++;
	j = num->decivaluesize - num->fractionsize + num->exp;
	while (i < num->decivaluesize)
	{
		num->decivalue[j] = num->decivalue[i];
		i++;
		j++;
	}
	return (j);
}

int				reorganizeexp(t_splitdouble *num)
{
	int			i;
	int			number;

	i = 0;
	while (i < num->intvaluesize && !num->intvalue[i])
		i++;
	if (i < num->intvaluesize)
	{
		num->bitdec++;
		number = num->intvalue[i];
		i++;
	}
	if (i < num->intvaluesize)
		num->decistart = num->decivaluesize - num->bitdec - (num->intvaluesize - i) + 1;
	else if (i == num->intvaluesize && num->intvalue[num->intvaluesize - 1])
		num->isexponentzero = 1;
	while (i < num->intvaluesize)
	{
		num->decivalue[num->decivaluesize - num->bitdec - (num->intvaluesize - i) + 1] = num->intvalue[i];
		num->exponentf++;
		i++;
	}
	if (num->exponentf || num->isexponentzero)
	{
		num->bitdec += num->exponentf - 1;
		tabinit(num->intvalue, num->intvaluesize);
		num->intvalue[i - 1] = number;
	}
	else
	{
		num->decistart = decistartset(num);
//		printf("num->decistart %d\n", num->decistart);
	//	num->decistart += (!num->intbit && num->exp < 0) ? -1 : 0; ptet decommenter plus tard
	}
	return (1);
}

int				splitdecivalue(char units[], t_splitdouble *num, char value[4096])
{
	int			i;
	int			actualbyte;
	int			actualbit;

	actualbyte = num->bytepos;
	actualbit = num->bitpos;
	i = 0;
//	while (i < 4096)
//	{
//		ft_printf("value[%d] = %hhb\n", i, value[i]);
//		i++;
//	}
//	i = 0;
	while (i < num->bitdec)
	{
		tabmul(num->decivalue, num->decivaluesize, 10);
		if (value[actualbyte] & (0x80U >> actualbit)) // voir pourquoi je dois +1 ici
//		{
//			write(1, "1", 1);
			tabadd(num->decivalue, num->decivaluesize, units);
//		}
//		else
//			write(1, "0", 1);
		actualbyte += (actualbit + 1 == 8) ? 1 : 0;
		actualbit = (actualbit + 1 == 8) ? 0 : actualbit + 1;
		tabmul(units, num->decivaluesize, 5);
		i++;
	}
//	write(1, "\n", 1);
	return (1);
}

int				splitintvalue(char units[], t_splitdouble *num, char value[4096])
{
	int			i;
	int			actualbyte;
	int			actualbit;

	actualbyte = num->bytepos - ((num->bitpos - 1 >= 0) ? 0 : 1);
	actualbit = (num->bitpos - 1 >= 0) ? num->bitpos - 1 : 7;
	i = 0;
	while (i < num->bitint)
	{
		if (value[actualbyte] & (0x80 >> actualbit))
			tabadd(num->intvalue, num->intvaluesize, units);
		actualbyte -= (actualbit - 1 < 0) ? 1 : 0;
		actualbit = (actualbit - 1 < 0) ? 7 : actualbit - 1;
		tabmul(units, num->intvaluesize, 2);
		i++;
	}
	return (1);
}

int				splitvalues(t_splitdouble *num, char value[4096])
{
	static char units[16445];

	tabinit(units, num->intvaluesize);
	units[num->intvaluesize - 1] = 1;
	splitintvalue(units, num, value);
	tabinit(units, num->decivaluesize);
	units[num->decivaluesize - 1] = 5;
	splitdecivalue(units, num, value);
	setcharvalue(num);
	return (1);
}

int				splitvaluesexp(t_splitdouble *num, char value[4096])
{
	static char units[16445];
	
	tabinit(units, num->intvaluesize);
	units[num->intvaluesize - 1] = 1;
	splitintvalue(units, num, value);
	tabinit(units, num->decivaluesize);
	units[num->decivaluesize - 1] = 5;
	splitdecivalue(units, num, value);
	reorganizeexp(num);
	setcharvalue(num);
	return (1);
}

int				separatenumber(t_splitdouble *num)
{
	static char	bytes[4096]; 
	int			bit;
	int			actualbyte;
	int			actualbit;

	bit = 0;
	tabinit(bytes, num->bytebufferlimit);
	actualbyte = num->bytepos - ((num->bitpos - 1 < 0) ? 1 : 0);
	actualbit = (num->bitpos - 1 < 0) ? 7 : num->bitpos - 1;
	while (bit < num->fractionsize + 1)
	{
		if (num->fraction & ((1ULL << num->fractionsize) >> bit))
			bytes[actualbyte] |= (0x80 >> actualbit);
		bit++;
		actualbyte += (actualbit + 1 == 8) ? 1 : 0;
		actualbit = (actualbit + 1 == 8) ? 0 : actualbit + 1;
	}
	num->bytepos = ((num->bytepos * 8 + num->bitpos + num->exp) / 8);
	num->bitpos = (num->bytepos * 8 + num->bitpos + num->exp) % 8;
	num->bitpos = (num->bitpos < 0) ? 8 + num->bitpos : num->bitpos;
	num->bitint = (1 + num->exp < 0) ? 0 : 1 + num->exp;
	num->bitdec = (num->fractionsize - num->exp < 0) ? 0 : num->fractionsize - num->exp;
	splitvalues(num, bytes);
	return (1);
}

int				separatenumberexp(t_splitdouble *num)
{
	static char	bytes[4096]; 
	int			bit;
	int			actualbyte;
	int			actualbit;

	bit = 0;
	tabinit(bytes, num->bytebufferlimit);
	actualbyte = num->bytepos - ((num->bitpos - 1 < 0) ? 1 : 0);
	actualbit = (num->bitpos - 1 < 0) ? 7 : num->bitpos - 1;
	while (bit < num->fractionsize + 1)
	{
		if (num->fraction & ((1ULL << num->fractionsize) >> bit))
			bytes[actualbyte] |= (0x80 >> actualbit);
		bit++;
		actualbyte += (actualbit + 1 == 8) ? 1 : 0;
		actualbit = (actualbit + 1 == 8) ? 0 : actualbit + 1;
	}
	num->bytepos = ((num->bytepos * 8 + num->bitpos + num->exp) / 8);
	num->bitpos = ((num->bytepos * 8 + num->bitpos + num->exp) % 8);
	num->bitpos = (num->bitpos < 0) ? 8 + num->bitpos : num->bitpos;
	num->bitint = (1 + num->exp < 0) ? 0 : 1 + num->exp;
	num->bitdec = (num->fractionsize - num->exp < 0) ? 0 : num->fractionsize - num->exp;
	splitvaluesexp(num, bytes);
	return (1);
}

int							mustroundhex(char val[], int numtocheck, int size)
{
	int						i;

	i = numtocheck;
	while (i < size - 1)
	{
		i++;
		if (val[i] < 8)
		   return (0);
		else if (val[i] > 8 || (val[i] == 8 && i == size - 1))
			return (1);	
	}
	return (1);
}

int							roundinghexa(char values[], int prec, char *rounding)
{
	int						i;

	if (!(prec < 0 || prec > 15))
	{
		i = prec;
		if (mustroundhex(values, i, 16))
		{
			values[i] += 1;
			while (i >= 0)
			{
				if (values[i] == 16)
				{
					values[i] = 0;
					if (i - 1 >= 0)
						values[i - 1] += 1;
					else
						(*rounding) += 1;
				}
				i--;
			}
		}
	}
	return (1);
}

int							calculatehexa(t_splitdouble *num, int offset, int prec)
{
	char		rounding;
	char		values[16];
	int			i;

	rounding = 0;
	i = 0;
	while (i < 16)
	{
		values[i] = 0;
		i++;
	}
	i = 0;
	while (i < 16 && offset < num->fractionsize)
	{
		values[i] = ((num->fraction & (0b1111ull << (num->fractionsize - 3 - offset))) >> (num->fractionsize - 3 - offset));
		offset += 4;
		i++;
	}
	roundinghexa(values, prec, &rounding);
	i = 0;
	while (i < 15)
	{
		values[i] += ((values[i] <= 9) ? '0' : 'a' - 10);
		i++;
	}
	if (rounding == 1)
		num->exp -= 3;
	rounding += '0';
	if (rounding != '0')
	{
		num->intvalue[0] = rounding;
		i = 0;
		while (i < 16)
		{
			num->decivalue[i] = values[i];
			i++;
		}
	//	write(1, &rounding, 1);
	//	write(1, ".", 1);
	//	write(1, values, 16);
		num->decivaluesize = 16;
	}
	else
	{
		num->intvalue[0] = values[0];
		i = 1;
		while (i < 16)
		{
			num->decivalue[i - 1] = values[i];
			i++;
		}
		num->decivaluesize = 15;
//		write(1, values, 1);
//		write(1, ".", 1);
//		write(1, values + 1, 15);
	}
//	printf("p%+d\n", num->exp);
//	write(1, "\nTEST\n", 6);
	return (1);
}

int							separatenumberhexa(t_splitdouble *num, int prec)
{
	char			intpart;
	int						i;

	i = 0;
	if (num->issub)
	{
		intpart = ((num->fraction & (0b1111ull << (num->fractionsize - 3))) >> (num->fractionsize - 3));
		while (!(intpart & 0b1000))
		{
			i++;
			intpart = ((num->fraction & (0b1111ull << (num->fractionsize - 3 - i))) >> (num->fractionsize - 3 - i));
		}
	}
	if (num->fractionsize == 52)
		i-=3;
	num->exp -= (3 + i);
	calculatehexa(num, i, prec);
//	num->intvalue[0] = intpart + ((intpart <= 9) ? '0' : 'a' - 10);
//	splitvaluesexp(num, bytes);
	return (1);
}
