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
	srand(43);
	srand(rand());
//	test = 10.35;
//	test2.val = 10.35;
	while (i < 100)
	{
		width = 20;
		length = 5;
		test3.value.sign = rand();
//		test3.value.exp = rand();
		test3.value.exp = rand();
//		test3.value.intpart = rand();
		test3.value.fra = (unsigned long int)rand() * (unsigned long int)rand();
		ft_printf("====================================\n");
		ft_printf("%#Lb\n", test3.val);
		ft_printf("%.*a\n", length, test3.val);
		printf("%.*a\n\n", length, test3.val);
		ft_printf("====================================\n");
//			test3.val = 9;
//		test3.val = 1.53634e-18;
//		test3.value.sign = 0;
//		test3.value.exponent = 0;
//		test3.value.intpart = 0;
//		test3.value.fraction = 0;
//		test3.value.exponent = 10;
//		test3.value.intpart = 1;
//		printf("exponent = %d, intpart = %d\n", test3.value.exponent == 0 ? 0 : test3.value.exponent- 16383, test3.value.intpart);
	//	ft_printf("BINAIRE {%#Lb}\n", test3.val, width, length);
//		printf("REAL {%*.*Le}\n", width, length, test3.val);
/*		printf("REAL {%.0e}\n", 11.5);
		printf("REAL {%.0e}\n", 12.5);
		printf("REAL {%.0e}\n", -11.5);
		printf("REAL {%.0e}\n\n", -12.5);
		ft_printf("MINE {%.0e}\n", 11.5);
		ft_printf("MINE {%.0e}\n", 12.5);
		ft_printf("MINE {%.0e}\n", -11.5);
		ft_printf("MINE {%.0e}\n\n\n\n", -12.5);

		printf("REAL {%.0f}\n", 11.5);
		printf("REAL {%.0f}\n", 12.5);
		printf("REAL {%.0f}\n", -11.5);
		printf("REAL {%.0f}\n\n", -12.5);
		ft_printf("MINE {%.0f}\n", 11.5);
		ft_printf("MINE {%.0f}\n", 12.5);
		ft_printf("MINE {%.0f}\n", -11.5);
		ft_printf("MINE {%.0f}\n\n\n\n", -12.5);

		printf("REAL {%.0a}\n", 11.5);
		printf("REAL {%.0a}\n", 12.5);
		printf("REAL {%.0a}\n", -11.5);
		printf("REAL {%.0a}\n", -12.5);
		ft_printf("MINE {%.0a}\n", 11.5);
		ft_printf("MINE {%.0a}\n", 12.5);
		ft_printf("MINE {%.0a}\n", -11.5);
		ft_printf("MINE {%.0a}\n\n\n\n", -12.5);
*/
		t_ldouble	test4;

		test4.value.sign = 0;
		test4.value.exp = 0;
		test4.value.intpart = 1;
		test4.value.fra = 0;//0x4000000000000000;


//		printf("%20.10Lf\n", test4.val);
//		ft_printf("MINE {%12.33f}\n\n", 378.31684027777771461842348799109459);
/*		printf("REAL {%*.*La}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n\n", width, length, test3.val);
		test3.value.exponent = 10;
		test3.value.intpart = 0;
		printf("exponent = %d, intpart = %d\n", test3.value.exponent== 0 ? 0 : test3.value.exponent- 16383, test3.value.intpart);
		ft_printf("BINAIRE {%#LLb}\n", test3.val, width, length);
		printf("REAL {%*.*Le}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n\n", width, length, test3.val);
		test3.value.intpart = 1;
		test3.value.exponent = 0;
		printf("exponent = %d, intpart = %d\n", test3.value.exponent== 0 ? 0 : test3.value.exponent- 16383, test3.value.intpart);
		ft_printf("BINAIRE {%#LLb}\n", test3.val, width, length);
		printf("REAL {%*.*Le}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n\n", width, length - 1, test3.val);
		test3.value.intpart = 0;
		test3.value.exponent = 0;
		printf("exponent = %d, intpart = %d\n", test3.value.exponent== 0 ? 0 : test3.value.exponent- 16383, test3.value.intpart);
		ft_printf("BINAIRE {%#LLb}\n", test3.val, width, length);
		printf("REAL {%*.*Le}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n", width, length, test3.val);
		printf("REAL {%*.*La}\n\n\n\n", width, length - 1, test3.val);
		ft_printf("REAL {%*.*Le}\n\n\n\n", width, length - 1, test3.val);
*/
//		printf("REAL {%.16000Lf}\n\n", test3.val);
//		ft_printf("MINE {%*.*Le}\n\n\n", width, length, test3.val);
//		printf("REAL {%*.*Lf}\n", width, length, test3.val);
//		printf("REAL {%*.*Lg}\n\n\n", width, length, test3.val);
//		ft_printf("MINE {%*.*Lf}\n", width, length, test3.val);
//		printf("REAL {%.160Lf}\n", test3.val);
//		ft_printf("MINE {%.160Lf}\n\n\n", test3.val);
//		printf("REAL {%.2000f}\n", test3.val);
//		ft_printf("MINE {%.2000f}\n\n", test3.val);
		i++;
	}
//	test = 1.7976e+308;
//	printf("REAL {%#20.20Lf}\n", test);
//	ft_printf("MINE {%20.20Lf}\n", test);
	return (1);
}
