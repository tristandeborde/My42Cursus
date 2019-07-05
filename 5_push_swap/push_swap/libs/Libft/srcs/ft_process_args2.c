/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:12:58 by tdeborde          #+#    #+#             */
/*   Updated: 2018/02/07 14:38:13 by tdeborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_process_long(va_list args)
{
	return ((intmax_t)(va_arg(args, long int)));
}

intmax_t	ft_process_longlong(va_list args)
{
	return ((intmax_t)va_arg(args, long long int));
}

intmax_t	ft_process_short(va_list args)
{
	return ((intmax_t)(short int)va_arg(args, int));
}

intmax_t	ft_process_shortshort(va_list args)
{
	return ((intmax_t)(char)va_arg(args, int));
}

uintmax_t	ft_process_ulonglong(va_list args)
{
	return ((uintmax_t)va_arg(args, long long int));
}
