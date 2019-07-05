/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:12:58 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/07 14:38:21 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	ft_process_ushortshort(va_list args)
{
	return ((uintmax_t)(unsigned char)va_arg(args, int));
}

uintmax_t	ft_process_usizet(va_list args)
{
	return ((uintmax_t)va_arg(args, size_t));
}

int			ft_process_pointer(va_list args, intmax_t (*f)(va_list),
		uintmax_t (*uf)(va_list), char **ret)
{
	intmax_t	ret_casted;

	f = &ft_process_longlong;
	(void)uf;
	ret_casted = f(args);
	*ret = ft_itoa_ubase(ret_casted, 16);
	if (!(*ret))
		*ret = ft_strnew(2);
	return (1);
}
