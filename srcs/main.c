/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 04:00:54 by toliver           #+#    #+#             */
/*   Updated: 2018/06/01 10:30:03 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int			main(void)
{
//	t_double split;
//	t_ldouble test2;
	/*
//	test = 2.22507e-308;
//	test = 3;
//	split.val = -1.7976e+308;
//	test = 1.7976e+308;
//	test = -2.2250738585072014e-308;
//	test = 2.2250738585072014e-307;
//	test = 0.1455;
	test = -1.7976e+308;
	printf("REAL {%10.2f}\n\n", test);
	ft_printf("MINE {%10.2f}\n\n", test);
	ft_printf("double = %#Lb\n", test);
	test = 2.2250738585072009e-308;
	printf("REAL {%.1075f}\n\n", test);
	ft_printf("MINE {%.1075f}\n\n", test);
	ft_printf("double = %#Lb\n", test);
	test = -10.24;
	printf("REAL {%010.2f}\n\n", test);
	ft_printf("MINE {%010.2f}\n\n", test);
	ft_printf("double = %#Lb\n", test);
	split.value.sign = 1;
	split.value.exponent = 0x7FF;
	split.value.fraction = 0;
	printf("REAL {%20.10f}\n\n", split.val);
	ft_printf("MINE {%20.10f}\n\n", split.val);
	ft_printf("double = %#Lb\n", split.val);
//	test = -0;
//	test = 10.25;
//	printf("REAL {%20.10f}\n\n", test);
//	ft_printf("MINE {%20.10f}\n\n", test);
//	ft_printf("double = %#Lb\n", test);
//	split.value.sign = 1;
//	split.value.exponent = 0x7FF;
//	split.value.fraction = 0;
	split.val = 20.25;
//	split.value.sign = 1;
//	split.value.exponent = 0x7FF;
//	split.value.fraction = 0;
	printf("REAL 20.10{%20.1000e}\n", split.val);
//	ft_printf("MINE 20.10f{%20.10f}\n", split.val);
	printf("REAL 020.10{%020.10e}\n", split.val);
//	ft_printf("MINE 020.10f{%020.10f}\n", split.val);
//	ft_printf("MINE {%020.10f}\n\n", split.val);
//	ft_printf("double = %#Lb\n", split.val);
	printf("REAL -20.10{%-20.10e}\n", split.val);
//	ft_printf("MINE -20.10f{%-20.10f}\n", split.val);
	printf("REAL \" 20.10e\"{% 20.10e}\n", split.val);
//	ft_printf("MINE \" 20.10f\"{% 20.10f}\n", split.val);
	printf("REAL \" -20.10e\"{% -20.10e}\n", split.val);
//	ft_printf("MINE \" -20.10f\"{% -20.10f}\n", split.val);
	printf("REAL \" 020.10e\"{% 020.10e}\n", split.val);
//	ft_printf("MINE \" 020.10f\"{% 020.10f}\n", split.val);
	printf("REAL \"0-20.10e\"{%0-20.10e}\n", split.val);
//	ft_printf("MINE \"0-20.10f\"{%0-20.10f}\n", split.val);
//	split.val = -10.25;
	printf("REAL 20.10{%20.10e}\n", split.val);
//	ft_printf("MINE 20.10f{%20.10f}\n", split.val);
	printf("REAL 020.10{%020.10e}\n", split.val);
//	ft_printf("MINE 020.10f{%020.10f}\n", split.val);
//	ft_printf("MINE {%020.10f}\n\n", split.val);
//	ft_printf("double = %#Lb\n", split.val);
	printf("REAL -20.10{%-20.10e}\n", split.val);
//	ft_printf("MINE -20.10f{%-20.10f}\n", split.val);
	printf("REAL \" 20.10e\"{% 20.10e}\n", split.val);
//	ft_printf("MINE \" 20.10f\"{% 20.10f}\n", split.val);
	printf("REAL \" -20.10e\"{% -20.10e}\n", split.val);
//	ft_printf("MINE \" -20.10f\"{% -20.10f}\n", split.val);
	printf("REAL \" 020.10e\"{% 020.10e}\n", split.val);
//	ft_printf("MINE \" 020.10f\"{% 020.10f}\n", split.val);
	printf("REAL \"0-20.10e\"{%0-20.10e}\n", split.val);
//	ft_printf("MINE \"0-20.10f\"{%0-20.10f}\n", split.val);
//	ft_printf("MINE {%-20.10f}\n\n", split.val);
//	ft_printf("double = %#Lb\n", split.val);
	t_ldouble	test2;
	test2.value.sign = 0;
	test2.value.exponent = 0x7FFE;
//	test2.value.exponent = 1;
	test2.value.intpart = 1;
	test2.value.fraction = 0x7FFFFFFFFFFFFFFF;
//	test2.value.fraction = 0;
//	test2.value.fraction += 0x4000000000000000;
//	test2.value.fraction += 0x2000000000000000;


//	printf("%.0Lf\n", test2.val);
	printf("%.16444Lf\n", test2.val);
	ft_printf("%.16444Lf\n", test2.val);
//	ft_printf("%#LLb\n", test2.val);
//	ft_printf("MINE {%.2000f}\n", test);
//	ft_printf("MINE {%.2000f}\n", test);
//	ft_printf("MINE {%.2000f}\n", test);
//	ft_printf("MINE {%.2000f}\n", test);
//	ft_printf("MINE {%.2000f}\n", test);
//	ft_printf("MINE {%.2000f}\n", test);
//	*/
//	
//	test = -2.2250738585072014e-308;
//	test2.value.sign = 0;
//	test2.value.exponent = 0x0;
//	test2.value.intpart = 1;
//	test2.value.fraction 
//= 0b111111111111111111111111111111111111111111111111111111111111;
	#include <stdlib.h>

//	long double		test;
	int				i;
	t_double		test3;
	int			width;
	int			length;

	i = 0;
	srand(42);
	srand(rand());
//	test = 10.35;
//	test2.val = 10.35;

	while (i < 1000)
	{
		width = (char)rand();
		length = (char)rand();
//		test3.value.sign = 0;//rand();
		test3.value.sign = rand();
//		test3.value.exp = 0b00110000101;//rand();
		test3.value.exp = (int)rand();
//		test3.value.intpart = rand();
//		test3.value.fra = 0b1101011110001110111001110001100000110110010111000000;//(unsigned long int)rand() * (unsigned long int)rand();
		test3.value.fra = (unsigned long int)rand() * (unsigned long int)rand();
		ft_printf("====================================\n");
		printf("width %d, length %d\n", width, length);
		ft_printf("%#Lb\n", test3.val);
		printf("%*.*a\n", width, length, test3.val);
//		printf("%-*e\n", width, length, test3.val);
//		printf("%-*.*a\n", width, length, test3.val);
		/*
		printf("%-*.*a\n", width, length - 1, test3.val);
		printf("%-*.*a\n", width, length - 2, test3.val);
		printf("%-*.*a\n", width, length - 3, test3.val);
		printf("%-*.*a\n", width, length - 4, test3.val);
		printf("%-*.*a\n", width, length - 5, test3.val);
		printf("%-*.*a\n", width, length - 6, test3.val);
		printf("%-*.*a\n", width, length - 7, test3.val);
		printf("%-*.*a\n", width, length - 8, test3.val);
		printf("%-*.*a\n", width, length - 9, test3.val);
		printf("%-*.*a\n", width, length - 10, test3.val);
		printf("%-*.*a\n", width, length - 11, test3.val);
		printf("%-*.*a\n", width, length - 12, test3.val);
		printf("%-*.*a\n", width, length - 13, test3.val);
		printf("%-*.*a\n", width, length - 14, test3.val);
		ft_printf("====================================\n");
		*/
		ft_printf("%*.*a\n", width, length, test3.val);
		/*
		ft_printf("%-*.*a\n", width, length - 1, test3.val);
		ft_printf("%-*.*a\n", width, length - 2, test3.val);
		ft_printf("%-*.*a\n", width, length - 3, test3.val);
		ft_printf("%-*.*a\n", width, length - 4, test3.val);
		ft_printf("%-*.*a\n", width, length - 5, test3.val);
		ft_printf("%-*.*a\n", width, length - 6, test3.val);
		ft_printf("%-*.*a\n", width, length - 7, test3.val);
		ft_printf("%-*.*a\n", width, length - 8, test3.val);
		ft_printf("%-*.*a\n", width, length - 9, test3.val);
		ft_printf("%-*.*a\n", width, length - 10, test3.val);
		ft_printf("%-*.*a\n", width, length - 11, test3.val);
		ft_printf("%-*.*a\n", width, length - 12, test3.val);
		ft_printf("%-*.*a\n", width, length - 13, test3.val);
		ft_printf("%-*.*a\n", width, length - 14, test3.val);
		ft_printf("====================================\n");
		*/
		i++;
	}
//	test = 1.7976e+308;
//	printf("REAL {%#20.20Lf}\n", test);
//	ft_printf("MINE {%20.20Lf}\n", test);
	return (1);
}
