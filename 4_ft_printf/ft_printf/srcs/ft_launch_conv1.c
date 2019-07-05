/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 17:12:22 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/26 17:31:42 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int		ft_read_zero(int i, t_opt *tab, char **str)
{
	int		len;
	char	*len_a;
	char	*len_a_trimmed;

	len_a_trimmed = NULL;
	len_a = ft_strsub(*str, 1, i);
	i = 0;
	if (!(len = ft_atoi_ubase(len_a, 10))
			|| ((len_a_trimmed = ft_itoa_ubase(len, 10))
				&& (ft_strlen(len_a) > ft_strlen(len_a_trimmed))))
	{
		while (ft_strcmp(tab[i].sym, "0"))
			i++;
		if (**str != '.')
			tab[i].is_true = 1;
	}
	free(len_a);
	if (len_a_trimmed)
		free(len_a_trimmed);
	return (len);
}

static int		ft_read_digits(char **str, t_opt *tab)
{
	uintmax_t		len;
	int				i;

	i = 0;
	while (ft_isdigit(**str))
	{
		i++;
		(*str)--;
	}
	if (!i || !(len = ft_read_zero(i, tab, str)))
		return (0);
	i = 0;
	if (**str == '.')
		while (ft_strcmp(tab[i].sym, "precision"))
			i++;
	else
		while (ft_strcmp(tab[i].sym, "width"))
			i++;
	tab[i].is_true = len;
	(*str)++;
	return (1);
}

void			ft_detect_long(t_opt *tab, char c,
		t_uf_convert *uf, t_f_convert *f)
{
	int	i;

	i = -1;
	while (++i < 15)
	{
		if (tab[i].is_true && tab[i].conv && ft_strchr("oOxXuU", c))
			*uf = tab[i].uconv;
		else if (tab[i].is_true && tab[i].conv)
			*f = tab[i].conv;
	}
	if (ft_isupper(c) && c != 'X')
	{
		*f = &ft_process_longlong;
		*uf = &ft_process_ulonglong;
	}
}

int				ft_read_flag(char *str, va_list args, char **ret)
{
	t_type		*types_tab;
	t_opt		*tab;
	int			i;
	char		c;

	tab = ft_init_opt_tab();
	types_tab = ft_init_type_tab();
	c = *str;
	if (ft_strchr("xXoO", c) && (i = ft_search_tab(tab, "base")))
		tab[i].is_true = ft_strchr("xX", c) ? 16 : 8;
	str--;
	while (*str != '%')
	{
		i = -1;
		if (!ft_read_digits(&str, tab))
			ft_save_flag(tab, str);
		if (*str != '%')
			str--;
	}
	*ret = ft_find_type(tab, types_tab, args, c);
	if (!(*ret))
		return (-1);
	(void)args;
	*ret = ft_isupper(c) && !ft_strchr("CS", c) ? ft_toupper_str(*ret) : *ret;
	return (ft_return_len(ret, tab, i, c));
}

int				ft_read_flag_noconv(char *str, va_list args, char **ret, char c)
{
	t_opt		*tab;
	int			i;

	(void)args;
	tab = ft_init_opt_tab();
	str--;
	while (*str != '%')
	{
		i = -1;
		if (!ft_read_digits(&str, tab))
			ft_save_flag(tab, str);
		if (*str != '%')
			str--;
	}
	if (!(*ret = ft_strnew(2)))
		return (0);
	**ret = c;
	ft_apply_options_char(ret, tab, c, i);
	return (ft_strlen(*ret));
}
