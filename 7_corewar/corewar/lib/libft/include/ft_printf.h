/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:28:21 by cmaxime           #+#    #+#             */
/*   Updated: 2018/04/25 16:47:26 by blefeuvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef enum	e_type
{
	T_NONE,
	T_HH,
	T_LL,
	T_H,
	T_L,
	T_Z,
	T_J
}				t_type;

typedef struct	s_print
{
	char		*buff;
	int			len;
	int			pib;
	int			ret;
	int			prev;
	int			hash;
	int			plus;
	int			minus;
	int			zero;
	int			space;
	int			size;
	int			precision;
	t_type		modifier;
	char		conv;
	int			force_h;
}				t_print;

typedef struct	s_cnv
{
	char		*cnv;
	t_print		(*f)(va_list ap, t_print p);
}				t_cnv;

typedef struct	s_pfop
{
	char		*op;
	t_print		(*f)(char *str, int *i, t_print p);
}				t_pfop;

int				ft_printf(const char *format, ...);
char			*ft_ltoa(uintmax_t n, size_t base);
char			*ft_ldtoa(long double n, int prec);
double			ft_powneg(int nb, int pow);
char			*ft_ldtoa_e(long double n, int prec);
t_print			pf_extractflag(char *str, int *i, t_print p);
t_print			pf_init_t_print(void);
t_print			pf_reinit_t_print(t_print p);
t_print			pf_update_t_print(char *str, int pos, t_print p);
t_print			pf_modifier_update(t_print p);
t_print			pf_collapse_buff(char *str, t_print p);
t_print			pf_collapse_char(char *str, int lenght, t_print p);
t_print			pf_flush_buff(t_print p);
t_print			pf_output_buff(t_print p);
int				pf_cmpchr(char *list, char c);
wchar_t			pf_check_mb_cur_max(void);
uintmax_t		pf_va_arg_int(va_list ap, t_print p);
uintmax_t		pf_va_arg_uint(va_list ap, t_print p);
void			*pf_va_arg_ptr(va_list ap, t_print p);
long double		pf_va_arg_dec(va_list ap, t_print p);
wchar_t			pf_va_arg_chr(va_list ap);
char			*pf_get_hexa_htag(void);
char			*pf_get_octa_htag(void);
char			*pf_add_hash(char *buff, t_print p);
char			*pf_add_precision(char *buff, t_print p);
char			*pf_add_size(char *buff, t_print p, int signe);
char			*pf_add_size_chr(char *buff, int *lenght, t_print p);
char			*pf_check_val_zero_exception(char *buff, uintmax_t n);
char			*ft_realloc_mem(char *s1, char const *s2,
		size_t len1, size_t len2);
char			**pf_get_list_flag(void);
t_pfop			*pf_get_op(void);
t_cnv			*pf_get_cnv(void);
char			*pf_wchar_to_char(wchar_t wc, int *lenght);
t_print			pf_op_hash(char *str, int *i, t_print p);
t_print			pf_op_zero(char *str, int *i, t_print p);
t_print			pf_op_space(char *str, int *i, t_print p);
t_print			pf_op_min(char *str, int *i, t_print p);
t_print			pf_op_plus(char *str, int *i, t_print p);
t_print			pf_op_size(char *str, int *i, t_print p);
t_print			pf_op_precision(char *str, int *i, t_print p);
t_print			pf_op_modifier(char *str, int *i, t_print p);
t_print			pf_op_conv(char *str, int *i, t_print p);
t_print			pf_arg_int(va_list ap, t_print p);
t_print			pf_arg_uint(va_list ap, t_print p);
t_print			pf_arg_str(va_list ap, t_print p);
t_print			pf_arg_chr(va_list ap, t_print p);
t_print			pf_arg_ptr(va_list ap, t_print p);
t_print			pf_arg_arg(va_list ap, t_print p);

t_print			pf_arg_dec(va_list ap, t_print p);
t_print			pf_arg_num(va_list ap, t_print p);
t_print			pf_arg_def(va_list ap, t_print p);

#endif
