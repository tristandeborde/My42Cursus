/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:34:52 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/30 13:10:56 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_opt
{
	char		*sym;
	int			is_true;
	intmax_t	(*conv)(va_list args);
	uintmax_t	(*uconv)(va_list args);
}				t_opt;

typedef struct	s_type
{
	char	*sym;
	int		(*conv)(va_list args, intmax_t(*f)(va_list),
			uintmax_t (*uf)(va_list), char **ret);
	int		(*ft_apply_options)(char **ret, t_opt *tab, char conv,\
			int error_code);
}				t_type;

typedef struct	s_padding
{
	char	padding;
	char	*(*f)(char *, const char *, size_t);
	char	*hashtag;
}				t_padding;

typedef	struct	s_format
{
	char	*ret;
	char	*str;
	char	*final_str;
	char	*tmp;
	int		len;
	int		len_save;
	int		len_tmp;
}				t_format;

typedef uintmax_t	(*t_uf_convert)(va_list);
typedef intmax_t	(*t_f_convert)(va_list);

int				ft_process_int(va_list args, intmax_t(*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_uint(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_char(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_str(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_octal(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_hexa(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_percent(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
int				ft_process_pointer(va_list args, intmax_t (*f)(va_list),\
		uintmax_t (*uf)(va_list), char **ret);
intmax_t		ft_process_short(va_list args);
intmax_t		ft_process_shortshort(va_list args);
intmax_t		ft_process_long(va_list args);
intmax_t		ft_process_longlong(va_list args);
intmax_t		ft_process_sizet(va_list args);
uintmax_t		ft_process_ushort(va_list args);
uintmax_t		ft_process_ushortshort(va_list args);
uintmax_t		ft_process_ulong(va_list args);
uintmax_t		ft_process_ulonglong(va_list args);
uintmax_t		ft_process_usizet(va_list args);
char			*ft_handle_unicode(wchar_t uni_char);
int				ft_handle_unistr(wchar_t *uni_char, char **ret);
int				ft_unistr_len(char *uni_str);
void			ft_unistr_trunc(char **str, int precision);
void			ft_n_bytes(wchar_t uni_char, int byte_nb, char **ret);
t_opt			*ft_init_opt_tab(void);
t_type			*ft_init_type_tab(void);
int				ft_check_conversion(char **format);
int				ft_check_height(char **format);
int				ft_check_precision(char **format);
int				ft_check_min_width(char **format);
int				ft_check_options(char **format);
int				ft_search_tab(t_opt *tab, char *key);
void			ft_place_sign(t_opt *tab, t_padding padding, char **ret,\
		char **tmp);
int				ft_apply_precision(char **ret, t_opt tab);
void			ft_write_padding(char **ret, t_opt *tab, t_padding padding,\
		char **tmp);
void			ft_write_padding_str(char **ret, t_opt *tab, t_padding padding,\
		char **tmp);
void			ft_write_padding_char(char **ret, t_opt *tab,\
		t_padding padding, char **tmp);
int				ft_apply_precision_int(char **ret, t_opt tab);
int				ft_apply_precision_char(char **ret, t_opt *tab, int error_code);
int				ft_apply_precision_str(char **ret, t_opt *tab, int error_code);
int				ft_apply_options_int(char **ret, t_opt *tab, char conv, \
		int error_code);
int				ft_apply_options_uint(char **ret, t_opt *tab, char conv,\
		int error_code);
int				ft_apply_options_str(char **ret, t_opt *tab, char conv,\
		int error_code);
int				ft_apply_options_percent(char **ret, t_opt *tab, char conv,\
		int error_code);
int				ft_apply_options_char(char **ret, t_opt *tab, char conv,\
		int error_code);
void			ft_apply_hashtag(char **ret, t_padding padding, char **tmp,\
		t_opt *tab);
int				ft_apply_space(char **ret, t_opt *tab);
void			ft_realloc(char **str, int is_dup, int width_i);
void			ft_offset_initialize(char **tmp, int width_i, int offset,
		t_padding padding);
char			*ft_simple_return(char *str1, const char *str2, size_t len);
t_padding		ft_find_padding(t_opt *tab, char conv);
t_padding		ft_find_padding_char(t_opt *tab);
t_padding		ft_find_padding_percent(t_opt *tab);
int				ft_read_flag(char *str, va_list args, char **ret);
int				ft_read_flag_noconv(char *str, va_list args,
		char **ret, char c);
void			ft_save_flag(t_opt *tab, char *str);
int				ft_return_len(char **ret, t_opt *tab, int i, char c);
char			*ft_find_type(t_opt *tab, t_type *types_tab,
		va_list args, char c);
void			ft_detect_long(t_opt *tab, char c,
			t_uf_convert *uf, t_f_convert *f);
int				ft_copy_char(char **str, char **final_str, int len);
int				ft_handle_noret(char **final_str, int *len_save,
		char **tmp, char **ret);
void			ft_free_null(char **str);
#endif
