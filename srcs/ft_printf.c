/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:32:16 by toliver           #+#    #+#             */
/*   Updated: 2018/05/03 06:36:20 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void							env_getarrayinit(t_env *env)
{
   	//getarg[CAT][LENGTH]
	int							i;
	int							j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 10)
			env->get_arg[i][j] = NULL;
	}
	env->get_arg[0][0] = &get_int;
	env->get_arg[0][1] = &get_char; // voir si je dois pas mettre int
	env->get_arg[0][2] = &get_short;
	env->get_arg[0][3] = &get_long;
	env->get_arg[0][4] = &get_longlong;
	env->get_arg[0][5] = &get_intmaxt;
	env->get_arg[0][6] = &get_sizet;
	env->get_arg[0][7] = &get_ptrdifft;
	env->get_arg[1][8] = &get_ldouble;
	env->get_arg[1][0] = &get_double;
	env->get_arg[2][0] = &get_int;
	env->get_arg[2][3] = &get_wintt;
	env->get_arg[3][0] = &get_ptr;
	env->get_arg[4][0] = &get_int;
	env->get_arg[4][1] = &get_char; // voir si je dois pas mettre int
	env->get_arg[4][2] = &get_short;
	env->get_arg[4][3] = &get_long;
	env->get_arg[4][4] = &get_longlong;
	env->get_arg[4][5] = &get_intmaxt;
	env->get_arg[4][6] = &get_sizet;
	env->get_arg[4][7] = &get_ptrdifft;
	env->get_arg[4][8] = &get_double;
	env->get_arg[4][9] = &get_ldouble;
	// ici si la fonction est a NULL on prend la fonction 0
}

void							env_ptrarrayinit(t_env *env)
{
	int							i;

	i = -1;
	while (++i < 128) // fill le plus possible les inutiles
		env->parse[i] = &parse_error; // ou une fonction d'erreur
//
//		FLAGS PARSING, decomment celles finies
//
//
	env->parse[48] = &parse_zeroflag;
	env->parse[43] = &parse_plusflag;
	env->parse[45] = &parse_minusflag;
	env->parse[32] = &parse_spaceflag;
	env->parse[35] = &parse_hashflag;
	env->parse[39] = &parse_apostropheflag;
//
//		AUTRE PARSING
//
	env->parse[46] = &parse_preci;
	env->parse[42] = &parse_wildchar;
	i = 49;
	while (i >= 49 && i <= 57)
	{
		env->parse[i] = &parse_number;
		i++;
	}
//
//		CONVERSION PARSING
//
	env->parse[106] = &parse_jconv;
	env->parse[122] = &parse_zconv;
	env->parse[76] = &parse_Lconv;
	env->parse[116] = &parse_tconv;
	env->parse[108] = &parse_lconv;
	env->parse[104] = &parse_hconv;
//
//		SIZE PARSING
//
	env->parse[37] = &parse_pcsize;  // %

	env->parse[100] = &parse_dsize;  // ints
	env->parse[68] = &parse_Dsize; // pareil que dsize avec le flag l
	env->parse[105] = &parse_dsize; // pareil que dsize (mais c'est i)
	env->parse[111] = &parse_osize; // ints unsigned en octal (commence par 0 avec # si ce n'est pas 0)
	env->parse[79] = &parse_Osize; // comme o mais avec un long int
	env->parse[117] = &parse_usize; // un unsigned
	env->parse[85] = &parse_Usize; // u avec l
	env->parse[120] = &parse_xsize;  // en hexa (commence par 0x avec # si ce n'est pas 0)
	env->parse[88] = &parse_Xsize; // en hexa maj (commence par 0X avec #)	


	env->parse[99] = &parse_csize;  // chars
	env->parse[67] = &parse_Csize; // widechar / c avec l	
	env->parse[115] = &parse_ssize; // string
	env->parse[83] = &parse_Ssize; // s avec l

	env->parse[110] = &parse_nsize; // ptr
	env->parse[112] = &parse_psize;



	env->parse[101] = &parse_esize; // float ici le # force le . meme si le nombre est entier	
	env->parse[69] = &parse_esize;
	env->parse[102] = &parse_fsize;
	env->parse[70] = &parse_fsize;
	env->parse[103] = &parse_gsize;
	env->parse[71] = &parse_gsize;
	env->parse[97] = &parse_asize;
	env->parse[65] = &parse_asize;


	env->parse[98] = &parse_bsize;  // affichage binaire	
	env->parse[66] = &parse_bsize;
}

void							env_init(t_env *env, const char *str)
{
	env->str = str;
	env->buffilasttoken = 0;
	env->buffi = 0;
	env->lastparam = 0;
	env->printflen = 0;
	env_ptrarrayinit(env);
	env_getarrayinit(env);
	env->null[0] = '(';
	env->null[1] = 'n';
	env->null[2] = 'u';
	env->null[3] = 'l';
	env->null[4] = 'l';
	env->null[5] = ')';
	env->null[6] = '\0';
}

/*
int								flag_set(t_arg *arg, char c)
{
	int							j;

	j = 0;
	while (c != FLAGS[j] && FLAGS[j] != '\0')
		j++;
	if (j < 6)
	{
		arg->flags = arg->flags | (1 << j);
		return (1);
	}
	return (0);
}
*/
int								ft_printf(const char *str, ...)
{
	t_env						env;

	if (str == NULL)
	{
		write(1, "Et non, je ne code pas avec le cul\n", 35);
		return (-1);
	}
	env_init(&env, str);
	va_start(env.arg, str);
	if (parse_string(&env) == -1)
	{
		buff_flush(&env);
		return (-1);
	}
	buff_flush(&env);
	return (env.printflen);
}
