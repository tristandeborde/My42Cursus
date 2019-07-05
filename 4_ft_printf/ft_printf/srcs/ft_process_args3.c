/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:12:58 by tdeborde          #+#    #+#             */
/*   Updated: 2018/01/25 18:53:19 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

intmax_t	ft_process_sizet(va_list args)
{
	return ((intmax_t)va_arg(args, size_t));
}

int			ft_process_hexa(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	uintmax_t	uret_casted;
	intmax_t	ret_casted;

	if (uf)
	{
		uret_casted = uf(args);
		*ret = ft_itoa_ubase(uret_casted, 16);
	}
	else if (f)
	{
		ret_casted = f(args);
		*ret = ft_itoa_ubase(ret_casted, 16);
	}
	else
		*ret = ft_itoa_ubase(va_arg(args, unsigned int), 16);
	if (!(*ret))
		*ret = ft_strnew(2);
	return (1);
}

int			ft_process_octal(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	uintmax_t	uret_casted;
	intmax_t	ret_casted;

	if (uf)
	{
		uret_casted = uf(args);
		*ret = ft_itoa_ubase(uret_casted, 8);
	}
	else if (f)
	{
		ret_casted = f(args);
		*ret = ft_itoa_ubase(ret_casted, 8);
	}
	else
		*ret = ft_itoa_ubase(va_arg(args, unsigned int), 8);
	if (!(*ret))
		*ret = ft_strnew(2);
	return (1);
}

uintmax_t	ft_process_ulong(va_list args)
{
	return ((uintmax_t)(va_arg(args, long int)));
}

uintmax_t	ft_process_ushort(va_list args)
{
	return ((uintmax_t)(unsigned short int)va_arg(args, int));
}
