/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:12:58 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/07 14:38:06 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_process_uint(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	uintmax_t	uret_casted;
	intmax_t	ret_casted;

	if (uf)
	{
		uret_casted = uf(args);
		*ret = ft_itoa_ubase(uret_casted, 10);
	}
	else if (f)
	{
		ret_casted = f(args);
		*ret = ft_itoa_ubase(ret_casted, 10);
	}
	else
		*ret = ft_itoa_ubase(va_arg(args, unsigned int), 10);
	if (!(*ret))
		*ret = ft_strnew(2);
	return (1);
}

int		ft_process_int(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	intmax_t	ret_casted;

	uf = NULL;
	if (f)
	{
		ret_casted = f(args);
		*ret = ft_itoa_base(ret_casted, 10);
	}
	else
		*ret = ft_itoa_base(va_arg(args, int), 10);
	if (!(*ret))
		*ret = ft_strnew(2);
	return (1);
}

int		ft_process_char(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	wchar_t		arg;

	*ret = ft_strnew(2);
	uf = NULL;
	if (f == &ft_process_longlong || f == &ft_process_long)
	{
		arg = va_arg(args, wchar_t);
		free(*ret);
		*ret = ft_handle_unicode(arg);
	}
	else if (f)
		**ret = f(args);
	else
		**ret = va_arg(args, int);
	return (1);
}

int		ft_process_str(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	wchar_t	*arg;
	char	*tmp;
	int		i;

	i = 1;
	uf = NULL;
	if (!args)
		return (0);
	if (f == &ft_process_longlong || f == &ft_process_long)
	{
		if (!(arg = va_arg(args, wchar_t *)))
			*ret = ft_strdup("(null)");
		else
			i = ft_handle_unistr(arg, ret);
	}
	else
	{
		if (!(tmp = (char *)va_arg(args, char *)))
			*ret = ft_strdup("(null)");
		else
			*ret = ft_strdup(tmp);
	}
	return (i);
}

int		ft_process_percent(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	(void)args;
	uf = NULL;
	f = NULL;
	*ret = ft_strnew(2);
	**ret = '%';
	return (1);
}
