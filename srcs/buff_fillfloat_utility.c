/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_utility.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 09:52:02 by toliver           #+#    #+#             */
/*   Updated: 2018/04/30 09:53:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				tabmul(char units[], int size, int multiplier)
{
	int			i;
	int			retenue;

	retenue = 0;
	i = size - 1;
	while (i >= 0)
	{
		units[i] = units[i] * multiplier + retenue;
		retenue = 0;
		if (units[i] > 9)
		{
			retenue = units[i] / 10;
			units[i] = units[i] % 10;
		}
		i--;
	}
	return (1);
}

int				tabadd(char units[], int unitssize, char toadd[])
{
	int			i;
	int			retenue;

	retenue = 0;
	i = unitssize - 1;
	while (i >= 0)
	{
		units[i] += toadd[i] + retenue;
		retenue = 0;
		if (units[i] > 9)
		{
			retenue = units[i] / 10;
			units[i] = units[i] % 10;
		}
		i--;
	}
	return (1);
}


