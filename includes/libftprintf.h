/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:30:16 by toliver           #+#    #+#             */
/*   Updated: 2018/04/14 20:00:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <wchar.h>
# include <stddef.h>

# define ALL "cCdDioOuUxXeEfFgGaAnpsS-+0 #'jzLtlh.123456789"
# define ALLBUTTYPE "S-+0 #'jzLtlh.123456789"
# define NUMBERS "0123456789"

# define TYPE "cCdDioOuUxXeEfFgGaAnpsS"  // flag delivat, L ?? il va ou ?

# define FLOATS "aAeEfFgG"
# define INTS "dDioOuUixX"
# define SIGNED "aAdDeEfFgGi"
# define UNSIGNED "uUoOxX"
# define CHARS "cCsS"
# define PTRS "np"

# define FLAGS "0-+ #'" // 0 handled in numbers
# define CONVERSION "jzLtlh" // ll et hh = 6 et 7
# define BUFFSIZE 2048
# define ARG arg->argument
/*
enum e_type {I, SC, SI, LI, LLI, IMAX, SIZ, PTD, UI, UC, USI, ULI, ULLI, UIMAX, DO,
	LD, WI, CPTR, WCPTR, VPTR, IPTR, SCPTR, SIPTR, LIPTR, LLIPTR, IMAXPTR,
   SIZPTR, PTDPTR};

enum e_conv {j, z, L, t, l, ll, h, hh};

enum e_size {c, C, d, D, i, o, O, u, U, x, X, e, E, f, F, g, G, a, A, n, p, s, S};

typedef struct		s_flags
{
	enum e_flags	flag;
	void			(*function[6])(char*);
}					t_flags;
*/


typedef union		u_types
{
/*
**	INTEGERS
*/
	int						i;	
	signed char				sc;
	short int				si;
	long int				li;
	long long int			lli;
	intmax_t				imax;
	size_t					siz;
	ptrdiff_t				ptd;
/*
**	UNSIGNED INTEGERS
*/
	unsigned int			ui;
	unsigned char			uc;
	unsigned short int		usi;
	unsigned long int		uli;
	unsigned long long int	ulli;
	uintmax_t				uimax;
/*
**	FLOATS
*/
	double					d;
	long double				ld;
/*
**	CHARS
*/
	wint_t					wi;
/*
**	STRINGS
*/
	char*					cptr;
	wchar_t*				wcptr;
/*
**	n
*/
	void*					vptr;
/*
**	p
*/
	int*					iptr;
	signed char*			scptr;
	short int*				siptr;
	long int*				liptr;
	long long int*			lliptr;
	intmax_t*				imaxptr;
	size_t*					sizptr;
	ptrdiff_t*				ptdptr;
}					t_types;

typedef struct		s_arg
{
	int				param;
	char			flags; // - / + / 0 /  / # / ' /
	int				width;
	int				prec;
	int				length;	
	int				type;
	int				cat; // cat - 0 = dDiuoxX, 1 = fFeEgGaA, 2 = c, 3 = s,p,n
	t_types			argument;
}					t_arg;

typedef struct		s_env
{
	const char		*str;
	char			buff[BUFFSIZE];
	int				printflen;
	int				buffilasttoken;
	int				buffi;
	int				lastparam;
	va_list			arg;
	int				(*parse[255])(struct s_env*, t_arg*);
	int				(*get_arg[4][9])(struct s_env*, t_arg*);
	char			null[7];
}					t_env;

int					ft_printf(const char *str, ...) __attribute__((format(printf,1,2)));

/*
** BUFFER FILLING FUNCTIONS
*/

int					parse_string(t_env *env);
int					parse_token(t_env *env);

int					parse_minusflag(t_env *env, t_arg *arg);
int					parse_plusflag(t_env *env, t_arg *arg);
int					parse_zeroflag(t_env *env, t_arg *arg);
int					parse_spaceflag(t_env *env, t_arg *arg);
int					parse_hashflag(t_env *env, t_arg *arg);
int					parse_apostropheflag(t_env *env, t_arg *arg);

int					parse_wildchar(t_env *env, t_arg *arg);
int					parse_number(t_env *env, t_arg *arg);
int					parse_error(t_env *env, t_arg *arg);
int					parse_preci(t_env *env, t_arg *arg);

int					parse_jconv(t_env *env, t_arg *arg);
int					parse_zconv(t_env *env, t_arg *arg);
int					parse_Lconv(t_env *env, t_arg *arg);
int					parse_tconv(t_env *env, t_arg *arg);
int					parse_lconv(t_env *env, t_arg *arg);
int					parse_hconv(t_env *env, t_arg *arg);

int					get_int(t_env *env, t_arg *arg);
int					get_char(t_env *env, t_arg *arg);
int					get_short(t_env *env, t_arg *arg);
int					get_long(t_env *env, t_arg *arg);
int					get_longlong(t_env *env, t_arg *arg);
int					get_intmaxt(t_env *env, t_arg *arg);
int					get_sizet(t_env *env, t_arg *arg);
int					get_ptrdifft(t_env *env, t_arg *arg);
int					get_ldouble(t_env *env, t_arg *arg);
int					get_double(t_env *env, t_arg *arg);
int					get_int(t_env *env, t_arg *arg);
int					get_wintt(t_env *env, t_arg *arg);
int					get_ptr(t_env *env, t_arg *arg);

intmax_t			get_castedintmaxt(t_arg *arg);
intmax_t			get_casteduintmaxt(t_arg *arg);

int					parse_pcsize(t_env *env, t_arg *arg);
int					parse_dsize(t_env *env, t_arg *arg);
int					parse_Dsize(t_env *env, t_arg *arg);
int					parse_osize(t_env *env, t_arg *arg);
int					parse_Osize(t_env *env, t_arg *arg);
int					parse_usize(t_env *env, t_arg *arg);
int					parse_Usize(t_env *env, t_arg *arg);
int					parse_xsize(t_env *env, t_arg *arg);
int					parse_Xsize(t_env *env, t_arg *arg);
int					parse_csize(t_env *env, t_arg *arg);
int					parse_Csize(t_env *env, t_arg *arg);
int					parse_ssize(t_env *env, t_arg *arg);
int					parse_Ssize(t_env *env, t_arg *arg);
int					parse_nsize(t_env *env, t_arg *arg);
int					parse_psize(t_env *env, t_arg *arg);


void				flags_cleanup(t_arg *arg); // pasur
void				fill_buffer(t_env *env, char c, int i);
int					get_arg(t_env *env, t_arg *arg);
void				arg_parse(t_env *env, t_arg *arg);

int					buff_fillc(t_env *env, t_arg *arg);
int					buff_fillwchar(t_env *env, t_arg *arg);
int					buff_putwchar(t_env *env, wint_t unicode);
int					buff_fills(t_env *env, t_arg *arg);
int					buff_fillwstr(t_env *env, t_arg *arg);
int					buff_fillint(t_env *env, t_arg *arg);
int					buff_filloct(t_env *env, t_arg *arg);
int					buff_fillhexa(t_env *env, t_arg *arg);

int					buff_filluint(t_env *env, t_arg *arg);

int					buff_fillchar(t_env *env, t_arg *arg);

int					buff_fillptr(t_env *env, t_arg *arg);
/*
** BUFFER HANDLING FUNCTIONS
*/

void				buff_flush(t_env *env);
void				buff_check(t_env *env);
int					buff_padding(t_env *env, t_arg *arg, int width);
int					buff_fillwith(t_env *env, char c);
int					buff_fillwithstr(t_env *env, char *str);
int					buff_fillwithnumber(t_env *env, char c, int i);
int					buff_padding(t_env *env, t_arg *arg, int width);

int					buff_uimaxtoahexa(t_env *env, uintmax_t value);

/*
** UTILITY
*/

void				arg_init(t_arg *arg);
void				env_init(t_env *env, const char *str);
void				env_ptrarrayinit(t_env *env);
void				env_getarrayinit(t_env *env);
int					pfatoi(t_env *env);



intmax_t			get_castedintmaxt(t_arg *arg);
size_t				ft_intmaxtlenbase(intmax_t value, int base);
size_t				ft_uintmaxtlenbase(uintmax_t value, int base);
int					octsize(wchar_t nbr);

int					buff_imaxtoa(t_env *env, intmax_t value);
int					buff_uimaxtoa(t_env *env, uintmax_t value);

#endif
