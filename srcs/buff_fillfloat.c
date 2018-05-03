/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 00:37:16 by toliver           #+#    #+#             */
/*   Updated: 2018/05/03 09:31:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					copyintexp(int *buffi, char buffer[], t_splitdouble *num)
{
	buffer[*buffi] = (num->intvalue[num->intvaluesize - 1] >= '0') ? num->intvalue[num->intvaluesize - 1] :'0';
	(*buffi)++;
	return (1);
}

int					writeexponent(t_env *env, t_splitdouble *num)
{
	buff_fillwith(env, (*env->str < 'a') ? 'E' : 'e');
	num->exponentf = (num->exp == 0 && num->fraction == 0) ? 0 : num->exponentf;
	buff_fillwith(env, (num->exponentf < 0) ? '-' : '+');
	if (num->exponentf < 10 && num->exponentf > -10)
		buff_fillwith(env, '0');
	buff_imaxtoa(env, num->exponentf);
	return (1);
}



int					copyint(int *buffi, char buffer[], int size, t_splitdouble *num)
{
	int				i;

	i = 0;
	if (!num->bitint)
	{
		buffer[*buffi] = '0';
		(*buffi)++;
		return (0);
	}
	while (!num->intvalue[i] && i < size)
		i++;
	if (i == size)
	{
		buffer[*buffi] = '0';
		(*buffi)++;
	}
	else
		while (i < size)
		{
			buffer[*buffi] = num->intvalue[i];
			(*buffi)++;
			i++;
		}
	return (1);
}

int					copydeci(int *buffi, char buffer[], int issharp, t_splitdouble *num)
{
	int				i;
	if (num->prec > 0 || issharp)
	{
		buffer[*buffi] = '.';
		(*buffi)++;
	}
	if (num->prec == 0)
		return (0);
	i = num->decivaluesize - num->bitdec;
	while (num->prec > 0 && i < num->decivaluesize)
	{
		buffer[*buffi] = num->decivalue[i];
		(*buffi)++;
		(num->prec)--;
		i++;	
	}
	return (1);
}
/*
int					copyerror(int *i, char buffer[], t_splitdouble *num, int ismaj)
{
	if (num->isinf)
	{
		buffer[*i] = 'i' - ismaj * 32;
		buffer[*i + 1] = 'n' - ismaj * 32;
		buffer[*i + 2] = 'f' - ismaj * 32;
	}
	else
	{
		buffer[*i] = 'n' - ismaj * 32;
		buffer[*i + 1] = 'a' - ismaj * 32;
		buffer[*i + 2] = 'n' - ismaj * 32;
	}
	num->prec = 3 + ((num->sign && num->fraction == 0) ? 1 : 0);
	return (1);
}
*/

int					copynumber(int *i, char buffer[], t_splitdouble *num, t_arg *arg)
{
	copyint(i, buffer, num->intvaluesize, num);
	copydeci(i, buffer, arg->flags & 2, num);
	return (1);
}

int					buff_putfloatsign(int sign, char flags, t_env *env)
{
	if (sign)
		buff_fillwith(env, '-');
	else if (flags & 4)
		buff_fillwith(env, ' ');
	else if (flags & 16)
		buff_fillwith(env, '+');
	return (1);
}

int					writenumberexp(t_env *env, t_arg *arg, t_splitdouble *num, char buf[])
{
	int				i;
	int				padding;
	

	i = 0;
	copyintexp(&i, buf, num);
	copydeci(&i, buf, arg->flags & 2, num);
//	write(1, buf, i); // pour le test
	while (buf[i] && i < num->finalbuffersize)
		i++;
	i += (num->sign || arg->flags & 4 || arg->flags & 16) ? 1 : 0;
	padding = arg->width - i - num->prec - 2 - ((ft_uintmaxtlenbase(num->exponentf, 10) < 2) ? 2 : ft_uintmaxtlenbase((num->exponentf > 0) ? num->exponentf : -num->exponentf, 10));
//	printf("arg->width %d, i %d, num->prec %d, len exp %zu\n", arg->width, i, num->prec, ft_uintmaxtlenbase((num->exponentf < 0) ? -num->exponentf : num->exponentf, 10));
//	printf("padding = %d\n", padding);
	if (arg->flags & 8 || arg->flags & 32 || arg->flags & 16)
		buff_putfloatsign(num->sign, arg->flags, env);
	if (!(arg->flags & 32))
		buff_padding(env, arg, padding);
	if (!(arg->flags & 8) && !(arg->flags & 32) && !(arg->flags & 16))
		buff_putfloatsign(num->sign, arg->flags, env);
	i = 0;
	while (buf[i])
	{
		buff_fillwith(env, buf[i]);
		i++;
	}
	while (num->prec)
	{
		buff_fillwith(env, '0');
		num->prec--;
	}
	writeexponent(env, num);
	if (arg->flags & 32)
		buff_padding(env, arg, padding);
	return (1);
}

int					writenumber(t_env *env, t_arg *arg, t_splitdouble *num, char buf[])
{
	int				i;
	int				padding;
	

	i = 0;
	copynumber(&i, buf, num, arg);
	while (buf[i] && i < num->finalbuffersize)
		i++;
	i += (num->sign || arg->flags & 4 || arg->flags & 16) ? 1 : 0;
	padding = arg->width - i - num->prec;
	if (arg->flags & 8 || arg->flags & 32 || arg->flags & 16)
		buff_putfloatsign(num->sign, arg->flags, env);
	if (!(arg->flags & 32))
		buff_padding(env, arg, padding);
	if (!(arg->flags & 8) && !(arg->flags & 32) && !(arg->flags & 16))
		buff_putfloatsign(num->sign, arg->flags, env);
	i = 0;
	while (buf[i])
	{
		buff_fillwith(env, buf[i]);
		i++;
	}
	while (num->prec)
	{
		buff_fillwith(env, '0');
		num->prec--;
	}
	if (arg->flags & 32)
		buff_padding(env, arg, padding);
	return (1);
}


int					writeerror(t_env *env, t_arg *arg, t_splitdouble *num)
{
	int				ismaj;
	int				padding;

	ismaj = (*env->str < 'a') ? 1 : 0; 
	padding = arg->width - 3 - ((num->sign && num->isinf) ? 1 : 0);
	if (!(arg->flags & 32))
		buff_padding(env, arg, padding);
	if (num->isinf)
	{
		if (num->sign)
			buff_fillwith(env, '-');
		buff_fillwith(env, 'i' - ismaj * 32);
		buff_fillwith(env, 'n' - ismaj * 32);
		buff_fillwith(env, 'f' - ismaj * 32);
	}
	else
	{
		buff_fillwith(env, 'n' - ismaj * 32);
		buff_fillwith(env, 'a' - ismaj * 32);
		buff_fillwith(env, 'n' - ismaj * 32);
	}
	if (arg->flags & 32)
		buff_padding(env, arg, padding);
	return (1);
}
int					buff_filldeci(t_env *env, t_arg *arg)
{
	t_splitdouble	final;
	static char		testbuffer[16448] = {0};

	splitinit(arg, &final);
	tabinit(testbuffer, final.finalbuffersize);
	if (!final.iserror)
	{
		separatenumber(&final);
		//ft_printf("sign = %b, intpart = %b, exponent = %b, fraction = %b\n", final.sign, final.intbit, final.exp, final.fraction);
//		ft_printf("%#LLb\n", arg->argument.ld); 
		roundingnumber(&final, arg->prec);
		writenumber(env, arg, &final, testbuffer);
	}
	else
		writeerror(env, arg, &final);
	return (1);
}

int					buff_fillexp(t_env *env, t_arg *arg)
{
	t_splitdouble	final;
	static char		testbuffer[16448] = {0};

	splitinit(arg, &final);
	tabinit(testbuffer, final.finalbuffersize);
	if (!final.iserror)
	{
		separatenumberexp(&final);
		//ft_printf("sign = %b, intpart = %b, exponent = %b, fraction = %b\n", final.sign, final.intbit, final.exp, final.fraction);
//		ft_printf("%#LLb\n", arg->argument.ld);
		roundingnumberexp(&final, arg->prec);
		writenumberexp(env, arg, &final, testbuffer);
//		write(1, env->buff, env->buffi);
//		write(1, env->str, 1);
	}
	else
		writeerror(env, arg, &final);
	return (1);
}
