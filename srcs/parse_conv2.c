/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:36:33 by toliver           #+#    #+#             */
/*   Updated: 2018/04/25 09:44:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_Lconv(t_env *env, t_arg *arg)
{
	env->str++;
	if (*env->str == 'L')
	{
		env->str++;
		arg->length = 9;
	}
	else
		arg->length = 8;
	return (1);
}
